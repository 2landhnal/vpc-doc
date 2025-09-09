// Cấu trúc cạnh (đồ thị có thể có trọng số âm)
struct Edge {
    int a, b, cost; // cạnh từ a -> b với trọng số cost
};

int n;                // số đỉnh
vector<Edge> edges;   // danh sách các cạnh
const int INF = 1000000000; // giá trị "vô cực"

// Hàm giải: tìm chu trình âm nếu có
void solve() {
    // B1: Khởi tạo
    vector<int> d(n, 0);     // khoảng cách, ban đầu cho tất cả = 0
                             // khác với Bellman-Ford chuẩn (thường gán INF)
                             // vì ta chỉ quan tâm đến việc tìm chu trình âm
    vector<int> p(n, -1);    // mảng parent để khôi phục đường đi
    int x;                   // lưu đỉnh bị cập nhật ở vòng lặp cuối

    // B2: Thực hiện n lần "relax" trên tất cả các cạnh
    for (int i = 0; i < n; ++i) {
        x = -1; // gán mặc định là không có cập nhật
        for (Edge e : edges) {
            // Nếu có thể cải thiện khoảng cách -> cập nhật
            if (d[e.a] + e.cost < d[e.b]) {
                d[e.b] = max(-INF, d[e.a] + e.cost); // chặn dưới tránh tràn số
                p[e.b] = e.a; // lưu cha của e.b để khôi phục chu trình
                x = e.b;      // đánh dấu có cập nhật xảy ra
            }
        }
    }

    // B3: Nếu không có cập nhật ở vòng lặp thứ n -> không có chu trình âm
    if (x == -1) {
        cout << "No negative cycle found.";
    } else {
        // B4: Nếu có cập nhật -> tồn tại chu trình âm
        // để chắc chắn x nằm trong chu trình, đi ngược lại n lần theo parent
        for (int i = 0; i < n; ++i)
            x = p[x];

        // B5: Khôi phục chu trình âm bằng cách đi theo parent đến khi lặp lại
        vector<int> cycle;
        for (int v = x;; v = p[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }
        reverse(cycle.begin(), cycle.end()); // đảo ngược để in đúng thứ tự

        // B6: In ra chu trình âm
        cout << "Negative cycle: ";
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
    }
}
