// Phù hợp khi m ≈ n (đồ thị ít cạnh).
const int INF = 1000000000;

struct Edge {
    int w, to;
    bool operator<(Edge const& other) const {
        return make_pair(w, to) < make_pair(other.w, other.to);
    }
};

int n;
vector<vector<Edge>> adj; // danh sách kề (mỗi cạnh có trọng số)

void prim() {
    int total_weight = 0;
    vector<Edge> min_e(n, {INF, -1}); 
    min_e[0].w = 0; 

    set<Edge> q; // giống priority queue
    q.insert({0, 0});

    vector<bool> selected(n, false);

    for (int i = 0; i < n; ++i) {
        if (q.empty()) {
            cout << "No MST!" << endl;
            exit(0);
        }

        // 1. Lấy đỉnh có cạnh nhẹ nhất
        int v = q.begin()->to;
        selected[v] = true;
        total_weight += q.begin()->w;
        q.erase(q.begin());

        // In cạnh đã chọn
        if (min_e[v].to != -1)
            cout << v << " " << min_e[v].to << endl;

        // 2. Cập nhật cạnh tối ưu cho các đỉnh kề
        for (Edge e : adj[v]) {
            if (!selected[e.to] && e.w < min_e[e.to].w) {
                q.erase({min_e[e.to].w, e.to}); // xóa giá trị cũ
                min_e[e.to] = {e.w, v};        // cập nhật cạnh tốt hơn
                q.insert({e.w, e.to});
            }
        }
    }

    cout << "MST weight = " << total_weight << endl;
}
