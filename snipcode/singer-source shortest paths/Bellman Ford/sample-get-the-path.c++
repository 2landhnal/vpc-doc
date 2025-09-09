void solve()
{
    // d[i] = khoảng cách ngắn nhất từ đỉnh nguồn v đến i
    vector<int> d(n, INF);
    d[v] = 0; // Khoảng cách từ v đến chính nó bằng 0

    // p[i] = đỉnh liền trước của i trong đường đi ngắn nhất (để khôi phục path)
    vector<int> p(n, -1);

    // Thuật toán Bellman–Ford (dạng cải tiến: lặp cho đến khi không còn cập nhật)
    for (;;) {
        bool any = false; // cờ báo có thay đổi khoảng cách trong vòng lặp này hay không

        // Duyệt qua toàn bộ các cạnh
        for (Edge e : edges)
            // Nếu đỉnh đầu e.a đã có khoảng cách hữu hạn
            if (d[e.a] < INF)
                // Nếu đi qua cạnh e sẽ ngắn hơn đường đi hiện tại đến e.b
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = d[e.a] + e.cost; // Cập nhật khoảng cách
                    p[e.b] = e.a;             // Lưu lại cha của e.b để reconstruct path
                    any = true;               // Đánh dấu có cập nhật
                }

        // Nếu không có cạnh nào được cập nhật nữa → thoát vòng lặp
        if (!any)
            break;
    }

    // Kiểm tra nếu không có đường từ v đến t
    if (d[t] == INF)
        cout << "No path from " << v << " to " << t << ".";
    else {
        // Truy vết lại đường đi bằng cách lần ngược từ t về v qua mảng p[]
        vector<int> path;
        for (int cur = t; cur != -1; cur = p[cur])
            path.push_back(cur);

        // Vì ta đi ngược từ t → v, nên phải đảo ngược để ra v → t
        reverse(path.begin(), path.end());

        // In kết quả
        cout << "Path from " << v << " to " << t << ": ";
        for (int u : path)
            cout << u << ' ';
    }
}
