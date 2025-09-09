void solve()
{
    vector<int> d(n, INF);   // d[i] = khoảng cách ngắn nhất từ v đến i
    d[v] = 0;                // từ v đến chính nó = 0
    vector<int> p(n, -1);    // p[i] = cha của i trong đường đi
    int x;                   // dùng để lưu đỉnh cuối cùng được cập nhật

    // Chạy n lần (thay vì n-1) để phát hiện chu trình âm
    for (int i = 0; i < n; ++i) {
        x = -1; // chưa có cập nhật
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    // cập nhật khoảng cách, tránh tràn số bằng max(-INF, ...)
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b; // lưu lại đỉnh được cập nhật cuối cùng
                }
    }

    if (x == -1) {
        // Nếu không có cập nhật ở vòng thứ n → không có chu trình âm
        cout << "No negative cycle from " << v;
    } else {
        // Có chu trình âm
        int y = x;
        // đi ngược n lần để chắc chắn rơi vào 1 đỉnh thuộc chu trình âm
        for (int i = 0; i < n; ++i)
            y = p[y];

        // Tái tạo chu trình âm bằng cách lần theo p[] cho đến khi quay lại y
        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        cout << "Negative cycle: ";
        for (int u : path)
            cout << u << ' ';
    }
}
