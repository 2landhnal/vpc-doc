struct Edge {
    int to, w;   // 'to' là đỉnh kề, 'w' là trọng số cạnh
};

int n;                        // số đỉnh trong đồ thị
vector<vector<Edge>> adj;     // danh sách kề: adj[u] chứa các cạnh xuất phát từ u

const int INF = 1e9;          // giá trị "vô cực" để khởi tạo khoảng cách

// Tìm đường đi ngắn nhất từ v0 đến tất cả các đỉnh khác
// d[u] = độ dài đường đi ngắn nhất từ v0 -> u
// p[u] = đỉnh cha (truy vết đường đi)
void shortest_paths(int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);     // ban đầu gán tất cả khoảng cách = INF
    d[v0] = 0;            // khoảng cách từ v0 đến chính nó = 0
    
    // m[u] đánh dấu trạng thái của đỉnh u trong queue:
    //   0 = đã ra khỏi queue (không còn trong hàng đợi)
    //   1 = đang ở trong queue
    //   2 = chưa từng được đưa vào queue
    vector<int> m(n, 2);

    deque<int> q;         // dùng deque để push_front / push_back
    q.push_back(v0);      // bắt đầu từ đỉnh nguồn

    p.assign(n, -1);      // chưa có cha nào

    // thuật toán chính
    while (!q.empty()) {
        int u = q.front();    // lấy đỉnh đầu hàng đợi
        q.pop_front();
        m[u] = 0;             // đánh dấu: u đã lấy ra (ra khỏi queue)

        // duyệt tất cả cạnh xuất phát từ u
        for (Edge e : adj[u]) {
            // nếu tìm thấy đường đi ngắn hơn đến e.to qua u
            if (d[e.to] > d[u] + e.w) {
                d[e.to] = d[u] + e.w;  // cập nhật khoảng cách
                p[e.to] = u;           // lưu cha để truy vết đường đi

                if (m[e.to] == 2) {
                    // nếu e.to chưa từng vào queue, cho vào cuối
                    m[e.to] = 1;
                    q.push_back(e.to);

                } else if (m[e.to] == 0) {
                    // nếu e.to đã ra khỏi queue trước đó, nay cần relax lại
                    // thì đẩy vào đầu để xử lý ngay (ưu tiên cập nhật)
                    m[e.to] = 1;
                    q.push_front(e.to);
                }
                // còn nếu m[e.to] == 1 (đang trong queue) thì không cần thêm lại
            }
        }
    }
}
