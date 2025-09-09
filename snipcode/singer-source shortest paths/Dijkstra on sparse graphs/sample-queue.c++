const int INF = 1000000000; 
// Giá trị "vô cùng" dùng để khởi tạo khoảng cách ban đầu (rất lớn, coi như chưa đi được)

vector<vector<pair<int, int>>> adj; 
// adj[u] = danh sách các cạnh kề của đỉnh u
// mỗi cạnh được lưu dưới dạng (đỉnh_kề, trọng_số)


// Hàm Dijkstra: tìm đường đi ngắn nhất từ đỉnh s đến tất cả các đỉnh khác
// d[u] = khoảng cách ngắn nhất từ s đến u
// p[u] = đỉnh cha của u trên đường đi ngắn nhất (dùng để phục hồi path)
void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size(); // số lượng đỉnh trong đồ thị
    d.assign(n, INF);   // ban đầu: mọi đỉnh đều cách s một khoảng cách "vô cùng"
    p.assign(n, -1);    // ban đầu: chưa có cha nào được xác định

    d[s] = 0; // Khoảng cách từ s tới chính nó bằng 0

    using pii = pair<int, int>; 
    // kiểu dữ liệu tiện lợi: (khoảng_cách, đỉnh)

    // Hàng đợi ưu tiên (min-heap): luôn lấy ra đỉnh có khoảng cách nhỏ nhất
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s}); // Bắt đầu từ đỉnh s với khoảng cách 0

    // Ý tưởng: mỗi lần lấy đỉnh có d[v] nhỏ nhất chưa xử lý ra khỏi heap,
    // sau đó "relax" (thư giãn) tất cả các cạnh xuất phát từ nó.
    while (!q.empty()) {
        int v = q.top().second; // đỉnh có khoảng cách nhỏ nhất hiện tại
        int d_v = q.top().first; // khoảng cách tương ứng
        q.pop();

        // Nếu giá trị trong heap đã lỗi thời (do d[v] đã được cập nhật tốt hơn), bỏ qua
        if (d_v != d[v])
            continue;

        // Duyệt tất cả các cạnh (v -> to) với trọng số len
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            // Nếu tìm được đường đi ngắn hơn đến 'to' thông qua 'v'
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len; // cập nhật khoảng cách ngắn nhất
                p[to] = v;          // cập nhật cha để sau còn truy vết path
                q.push({d[to], to}); // đưa đỉnh 'to' vào heap để xét tiếp
            }
        }
    }
}
