const int INF = 1000 * 1000 * 1000;

// a[i][j] = chi phí gán người i cho công việc j
vector<int> assignment(vector<vector<int>> a) {
    int n = a.size();         // số người và công việc (giả sử n x n)
    int m = n * 2 + 2;        // tổng số đỉnh trong đồ thị: n người + n công việc + source + sink
    vector<vector<int>> f(m, vector<int>(m)); // f[u][v] = luồng hiện tại trên cạnh u->v
    int s = m - 2, t = m - 1; // source và sink
    int cost = 0;              // tổng chi phí tối thiểu

    while (true) {
        vector<int> dist(m, INF);   // khoảng cách / chi phí để đi từ source đến mỗi đỉnh
        vector<int> p(m);           // lưu trữ parent (đỉnh trước đó trên đường đi)
        vector<bool> inq(m, false); // đánh dấu đỉnh có trong hàng đợi hay không
        queue<int> q;

        dist[s] = 0;
        p[s] = -1;
        q.push(s);

        // BFS / SPFA tìm đường augmenting path chi phí nhỏ nhất
        while (!q.empty()) {
            int v = q.front(); q.pop();
            inq[v] = false;

            if (v == s) {
                // từ source đi đến tất cả các người
                for (int i = 0; i < n; ++i) {
                    if (f[s][i] == 0) { // chỉ đi trên cạnh chưa có luồng
                        dist[i] = 0;
                        p[i] = s;
                        if (!inq[i]) { q.push(i); inq[i] = true; }
                    }
                }
            } else if (v < n) {
                // từ đỉnh người đi đến các công việc
                for (int j = n; j < n + n; ++j) {
                    if (f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n]) {
                        dist[j] = dist[v] + a[v][j - n];
                        p[j] = v;
                        if (!inq[j]) { q.push(j); inq[j] = true; }
                    }
                }
            } else {
                // từ đỉnh công việc quay lại các người (cạnh ngược để update luồng)
                for (int j = 0; j < n; ++j) {
                    if (f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n]) {
                        dist[j] = dist[v] - a[j][v - n];
                        p[j] = v;
                        if (!inq[j]) { q.push(j); inq[j] = true; }
                    }
                }
            }
        }

        // tìm công việc chưa được gán với chi phí nhỏ nhất
        int curcost = INF;
        for (int i = n; i < n + n; ++i) {
            if (f[i][t] == 0 && dist[i] < curcost) {
                curcost = dist[i];
                p[t] = i; // parent của sink là công việc này
            }
        }

        if (curcost == INF) // không còn đường augmenting path nào
            break;

        cost += curcost; // cộng chi phí của đường tìm được

        // tăng luồng trên đường tìm được
        for (int cur = t; cur != -1; cur = p[cur]) {
            int prev = p[cur];
            if (prev != -1)
                f[cur][prev] = -(f[prev][cur] = 1); // cập nhật luồng
        }
    }

    // dựng kết quả gán: người i được gán công việc j
    vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (f[i][j + n] == 1)
                answer[i] = j;
        }
    }
    return answer;
}