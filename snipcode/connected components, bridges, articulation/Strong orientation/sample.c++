vector<vector<pair<int, int>>> adj; // adjacency list: với mỗi đỉnh lưu (đỉnh kề, chỉ số cạnh)
vector<pair<int, int>> edges;       // danh sách cạnh: edges[i] = (u, v)

vector<int> tin, low;               // tin[v] = thời điểm DFS đầu tiên thăm v
                                    // low[v] = thời điểm nhỏ nhất có thể "quay ngược" từ v
int bridge_cnt;                     // đếm số bridge (cạnh cầu)
string orient;                      // chuỗi ký tự hướng của cạnh: '>' nghĩa theo chiều edges[i].first → edges[i].second,
                                    // '<' nghĩa ngược lại
vector<bool> edge_used;             // đánh dấu cạnh đã xử lý trong DFS chưa

// Hàm DFS để tìm bridge và gán hướng cho cạnh
void find_bridges(int v) {
    static int time = 0;           // thời gian DFS toàn cục
    low[v] = tin[v] = time++;      // gán thời gian vào tin và low ban đầu

    for (auto p : adj[v]) {
        if (edge_used[p.second]) continue;  // nếu cạnh này đã xử lý, bỏ qua
        edge_used[p.second] = true;         // đánh dấu cạnh đã dùng

        // Gán hướng cho cạnh p.second: 
        // nếu v là đầu first → gán '>', ngược lại '<'
        orient[p.second] = v == edges[p.second].first ? '>' : '<';

        int nv = p.first;          // đỉnh kề

        if (tin[nv] == -1) {       // nếu nv chưa được thăm
            find_bridges(nv);      // DFS tiếp nv
            low[v] = min(low[v], low[nv]); // cập nhật low[v]

            if (low[nv] > tin[v]) {
                // phát hiện một bridge giữa v và nv
                bridge_cnt++;
            }
        } else {
            // cạnh ngược / back edge → cập nhật low[v]
            low[v] = min(low[v], tin[nv]);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    adj.resize(n);
    tin.resize(n, -1);
    low.resize(n, -1);
    orient.resize(m);       // lưu hướng của m cạnh
    edges.resize(m);
    edge_used.resize(m);

    // đọc input m cạnh
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;                       // chuyển sang 0-based
        adj[a].push_back({b, i});       // thêm cạnh a-b với id = i
        adj[b].push_back({a, i});
        edges[i] = {a, b};              // lưu cạnh gốc
    }

    int comp_cnt = 0;                   // số connected components
    for (int v = 0; v < n; v++) {
        if (tin[v] == -1) {             // nếu v chưa được thăm
            comp_cnt++;
            find_bridges(v);            // DFS từ v
        }
    }

    // Kết quả:
    // comp_cnt + bridge_cnt = số strongly connected components
    // orient = chuỗi thể hiện hướng gán cho từng cạnh
    printf("%d\n%s\n", comp_cnt + bridge_cnt, orient.c_str());
}
