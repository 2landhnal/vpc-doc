const int INF = 1000000000; // giá trị vô cùng lớn, dùng để khởi tạo khoảng cách
vector<vector<pair<int, int>>> adj; 
// adj[v] = danh sách các cạnh xuất phát từ đỉnh v
// mỗi cạnh lưu dưới dạng pair(to, weight)

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size(); 
    d.assign(n, INF);   // d[v] = khoảng cách ngắn nhất từ s tới v (ban đầu vô cực)
    p.assign(n, -1);    // p[v] = đỉnh cha của v trên đường đi ngắn nhất
    vector<bool> u(n, false); // u[v] = true nếu v đã được "xử lý xong" (đỉnh cố định)

    d[s] = 0; // khoảng cách từ s đến chính nó là 0

    // Thuật toán chạy tối đa n bước (mỗi bước chọn 1 đỉnh chưa xét)
    for (int i = 0; i < n; i++) {
        int v = -1;

        // B1: tìm đỉnh v chưa xét (u[v] == false) có d[v] nhỏ nhất
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        // nếu không còn đỉnh nào có đường đi từ s (d[v] = INF), dừng
        if (d[v] == INF)
            break;

        // B2: đánh dấu đỉnh v đã được xử lý
        u[v] = true;

        // B3: duyệt tất cả cạnh (v -> to) và thử relax
        for (auto edge : adj[v]) {
            int to = edge.first;   // đỉnh kề
            int len = edge.second; // trọng số cạnh

            // Nếu đường đi qua v tốt hơn đường hiện tại tới "to" thì cập nhật
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v; // lưu lại đường đi: cha của "to" là v
            }
        }
    }
}

//======================================================================
// Hàm khôi phục đường đi:
vector<int> restore_path(int s, int t, vector<int> const& p) {
    vector<int> path;

    // bắt đầu từ đỉnh t, lần theo cha ngược về s
    for (int v = t; v != s; v = p[v])
        path.push_back(v);

    path.push_back(s); // thêm đỉnh gốc

    reverse(path.begin(), path.end()); // đảo ngược để có đường đi đúng thứ tự s -> t
    return path;
}


