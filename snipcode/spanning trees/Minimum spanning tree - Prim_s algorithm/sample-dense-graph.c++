// Phù hợp khi n lớn, m ~ n² (đồ thị đầy cạnh).
int n;
vector<vector<int>> adj; // ma trận kề (adj[i][j] = trọng số cạnh i-j hoặc INF)
const int INF = 1000000000;

struct Edge {
    int w = INF, to = -1; // w = trọng số nhỏ nhất, to = nối tới đỉnh nào
};

void prim() {
    int total_weight = 0;
    vector<bool> selected(n, false); // đánh dấu đỉnh đã chọn vào MST
    vector<Edge> min_e(n);           // min_e[v] = cạnh nhẹ nhất nối v với tập đã chọn
    min_e[0].w = 0;                  // bắt đầu từ đỉnh 0

    for (int i=0; i<n; ++i) {
        // 1. Tìm đỉnh v chưa chọn có cạnh nhỏ nhất
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
                v = j;
        }

        // Không tìm thấy => đồ thị không liên thông => không có MST
        if (min_e[v].w == INF) {
            cout << "No MST!" << endl;
            exit(0);
        }

        // 2. Chọn đỉnh v
        selected[v] = true;
        total_weight += min_e[v].w;

        // Nếu v không phải đỉnh đầu tiên thì in ra cạnh nối với nó
        if (min_e[v].to != -1)
            cout << v << " " << min_e[v].to << endl;

        // 3. Cập nhật min_e cho các đỉnh khác
        for (int to = 0; to < n; ++to) {
            if (adj[v][to] < min_e[to].w) {
                min_e[to] = {adj[v][to], v};
            }
        }
    }

    cout << "MST weight = " << total_weight << endl;
}
