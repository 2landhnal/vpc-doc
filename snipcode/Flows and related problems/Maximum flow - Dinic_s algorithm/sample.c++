// Cấu trúc cạnh với thông tin: đỉnh bắt đầu v, đỉnh kết thúc u, dung lượng cap và luồng flow hiện tại
struct FlowEdge {
    int v, u;                 // v: từ, u: đến
    long long cap, flow = 0;  // cap: dung lượng tối đa, flow: luồng hiện tại
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

// Thuật toán Dinic để tính luồng cực đại
struct Dinic {
    const long long flow_inf = 1e18; // giá trị lớn thay cho vô cực
    vector<FlowEdge> edges;          // danh sách tất cả các cạnh
    vector<vector<int>> adj;         // danh sách cạnh đi từ mỗi đỉnh (chứa index của edges)
    int n, m = 0;                    // n: số đỉnh, m: số cạnh
    int s, t;                         // s: source, t: sink
    vector<int> level;               // level[v]: mức của đỉnh v trong BFS (level graph)
    vector<int> ptr;                 // con trỏ ptr[v] để ghi nhớ cạnh đã thử trong DFS
    queue<int> q;                     // hàng đợi cho BFS

    // Khởi tạo với n đỉnh, nguồn s và bồn t
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    // Thêm cạnh (v->u) với dung lượng cap
    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap); // cạnh chính
        edges.emplace_back(u, v, 0);   // cạnh ngược để duy trì residual graph
        adj[v].push_back(m);           // thêm index cạnh vào adj list của v
        adj[u].push_back(m + 1);       // thêm index cạnh ngược vào adj list của u
        m += 2;                        // mỗi lần thêm 2 cạnh
    }

    // BFS để xây dựng level graph
    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                // bỏ qua nếu luồng đã đầy
                if (edges[id].cap == edges[id].flow)
                    continue;
                // bỏ qua nếu đỉnh đã được đánh level
                if (level[edges[id].u] != -1)
                    continue;
                // đánh level cho đỉnh u
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        // nếu không tới được sink t => không còn đường tăng luồng
        return level[t] != -1;
    }

    // DFS để đẩy luồng trong level graph
    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;           // luồng 0 thì thôi
        if (v == t)
            return pushed;      // đến sink => trả luồng đẩy được
        // duyệt các cạnh từ vị trí ptr[v] để tránh lặp lại
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            // chỉ đi qua cạnh tăng level
            if (level[v] + 1 != level[u])
                continue;
            // thử đẩy luồng
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            // cập nhật luồng trên cạnh và cạnh ngược
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    // Hàm tính luồng cực đại
    long long flow() {
        long long f = 0;
        while (true) {
            // tạo level graph mới
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())  // nếu không còn đường nào => dừng
                break;
            // reset con trỏ ptr cho DFS
            fill(ptr.begin(), ptr.end(), 0);
            // đẩy blocking flow trong level graph
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f; // trả về luồng cực đại
    }
};
