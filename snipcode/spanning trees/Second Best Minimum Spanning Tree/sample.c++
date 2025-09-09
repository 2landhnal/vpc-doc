// Cấu trúc cạnh
// Cách gán id trong code
// for (int i = 1; i <= m; i++) {
//     cin >> a >> b >> w; // đọc cạnh
//     edges.push_back({a, b, w, i - 1});
// }


struct edge {
    int s, e, w, id; // s: start, e: end, w: trọng số, id: chỉ số cạnh
    bool operator<(const struct edge& other) { return w < other.w; } // so sánh theo trọng số
};
typedef struct edge Edge;

const int N = 2e5 + 5;
long long res = 0, ans = 1e18; // res = MST cost, ans = second best MST cost
int n, m, a, b, w, id, l = 21; // l = log2(N) để LCA
vector<Edge> edges;
vector<int> h(N, 0), parent(N, -1), size(N, 0), present(N, 0);
// h: độ sâu node, parent + size: DSU, present[i]: cạnh i có nằm trong MST không
vector<vector<pair<int, int>>> adj(N), dp(N, vector<pair<int, int>>(l));
// adj[u]: (v, w) các cạnh MST
// dp[u][i] = (max, second_max) cạnh trên đường từ u lên tổ tiên 2^i
vector<vector<int>> up(N, vector<int>(l, -1)); // up[u][i] = tổ tiên 2^i của u

// Hàm combine: gộp hai cặp (max, second_max)
pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    vector<int> v = {a.first, a.second, b.first, b.second};
    int topTwo = -3, topOne = -2;
    for (int c : v) {
        if (c > topOne) {
            topTwo = topOne;
            topOne = c;
        } else if (c > topTwo && c < topOne) {
            topTwo = c;
        }
    }
    return {topOne, topTwo}; // trả về (max, second_max)
}

// DFS để build LCA + binary lifting
void dfs(int u, int par, int d) {
    h[u] = 1 + h[par];    // set depth
    up[u][0] = par;       // tổ tiên 2^0 = cha trực tiếp
    dp[u][0] = {d, -1};   // cạnh nối u-par, lưu max=d, second_max=-1
    for (auto v : adj[u]) {
        if (v.first != par) {
            dfs(v.first, u, v.second);
        }
    }
}

// Trả về (maxEdge, secondMaxEdge) trên đường giữa u và v
pair<int, int> lca(int u, int v) {
    pair<int, int> ans = {-2, -3};
    if (h[u] < h[v]) swap(u, v);

    // Nâng u lên cùng level với v
    for (int i = l - 1; i >= 0; i--) {
        if (h[u] - h[v] >= (1 << i)) {
            ans = combine(ans, dp[u][i]);
            u = up[u][i];
        }
    }
    if (u == v) return ans;

    // Nâng u và v đồng thời cho tới khi gặp tổ tiên chung
    for (int i = l - 1; i >= 0; i--) {
        if (up[u][i] != -1 && up[v][i] != -1 && up[u][i] != up[v][i]) {
            ans = combine(ans, combine(dp[u][i], dp[v][i]));
            u = up[u][i];
            v = up[v][i];
        }
    }
    // Kết hợp thêm cạnh cuối cùng (u-parent, v-parent)
    ans = combine(ans, combine(dp[u][0], dp[v][0]));
    return ans;
}

int main(void) {
    cin >> n >> m;

    // DSU init
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    // Đọc cạnh
    for (int i = 1; i <= m; i++) {
        cin >> a >> b >> w; // input 1-indexed
        edges.push_back({a, b, w, i - 1});
    }
    sort(edges.begin(), edges.end()); // sắp xếp theo trọng số

    // Kruskal để build MST
    for (int i = 0; i <= m - 1; i++) {
        a = edges[i].s;
        b = edges[i].e;
        w = edges[i].w;
        id = edges[i].id;
        if (unite_set(a, b)) { // nếu 2 đỉnh chưa nối -> thêm vào MST
            adj[a].emplace_back(b, w);
            adj[b].emplace_back(a, w);
            present[id] = 1;  // đánh dấu cạnh nằm trong MST
            res += w;         // cộng trọng số vào MST cost
        }
    }

    // DFS build LCA(Lowest Common Ancestor)
    dfs(1, 0, 0);

    // Build bảng binary lifting
    for (int i = 1; i <= l - 1; i++) {
        for (int j = 1; j <= n; ++j) {
            if (up[j][i - 1] != -1) {
                int v = up[j][i - 1];
                up[j][i] = up[v][i - 1];
                dp[j][i] = combine(dp[j][i - 1], dp[v][i - 1]);
            }
        }
    }

    // Thử thay từng cạnh ngoài MST vào
    for (int i = 0; i <= m - 1; i++) {
        id = edges[i].id;
        w = edges[i].w;
        if (!present[id]) { // chỉ xét cạnh không thuộc MST
            auto rem = lca(edges[i].s, edges[i].e); // max, second_max cạnh trên path
            if (rem.first != w) {
                ans = min(ans, res + w - rem.first);
            } else if (rem.second != -1) {
                ans = min(ans, res + w - rem.second);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
