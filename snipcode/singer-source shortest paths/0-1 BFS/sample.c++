// Số đỉnh n, đồ thị biểu diễn bằng danh sách kề adj
// adj[v] là vector các cạnh đi ra từ v, mỗi cạnh = {u, w}, với u là đỉnh đích, w ∈ {0,1}

// Khởi tạo khoảng cách từ s đến mọi đỉnh ban đầu là vô cùng lớn (INF)
vector<int> d(n, INF);
d[s] = 0;  // khoảng cách từ s đến chính nó bằng 0

// Dùng deque (hàng đợi 2 đầu) thay cho priority_queue
deque<int> q;
q.push_front(s); // bắt đầu từ đỉnh nguồn s

while (!q.empty()) {
    int v = q.front();   // lấy đỉnh ở đầu deque
    q.pop_front();

    // duyệt tất cả cạnh (v -> u) có trọng số w
    for (auto edge : adj[v]) {
        int u = edge.first;   // đỉnh kề
        int w = edge.second;  // trọng số cạnh (0 hoặc 1)

        // Nếu tìm được đường đi ngắn hơn đến u thông qua v
        if (d[v] + w < d[u]) {
            d[u] = d[v] + w;  // cập nhật khoảng cách

            // Nếu w = 1: đưa u vào cuối deque (xử lý sau)
            if (w == 1)
                q.push_back(u);

            // Nếu w = 0: đưa u vào đầu deque (ưu tiên xử lý ngay)
            else
                q.push_front(u);
        }
    }
}
