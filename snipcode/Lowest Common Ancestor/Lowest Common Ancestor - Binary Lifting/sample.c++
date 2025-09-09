int n, l;                    // n = số nút trong cây, l = log2(n)
vector<vector<int>> adj;     // danh sách kề của cây

int timer;                   // thời gian DFS dùng để đánh dấu tin/tout
vector<int> tin, tout;       // tin[v]: thời điểm DFS bắt đầu v, tout[v]: thời điểm DFS kết thúc v
vector<vector<int>> up;      // up[v][i] = tổ tiên của v cách 2^i bậc

// DFS để chuẩn bị bảng up và đánh dấu tin/tout
void dfs(int v, int p)
{
    tin[v] = ++timer;        // thời điểm vào nút v
    up[v][0] = p;            // tổ tiên 2^0 của v là cha p

    // Tính các tổ tiên 2^i dựa vào công thức up[v][i] = up[up[v][i-1]][i-1]
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    // Duyệt DFS các nút con
    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;       // thời điểm rời nút v
}

// Kiểm tra u có phải là tổ tiên của v không
bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

// Hàm tìm LCA của u và v
int lca(int u, int v)
{
    if (is_ancestor(u, v))  // nếu u là tổ tiên của v
        return u;
    if (is_ancestor(v, u))  // nếu v là tổ tiên của u
        return v;

    // nâng u lên các bậc 2^i sao cho u không còn là tổ tiên của v
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];         // cha trực tiếp của u bây giờ là LCA
}

// Hàm tiền xử lý
void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));              // log2(n) để biết số mức nhảy cần thiết
    up.assign(n, vector<int>(l + 1)); // khởi tạo bảng up
    dfs(root, root);                 // bắt đầu DFS từ gốc
}
