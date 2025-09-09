int n; // số lượng nút trong đồ thị
vector<vector<int>> capacity; // capacity[u][v] = dung lượng còn lại của cạnh (u -> v)
vector<vector<int>> adj;      // danh sách kề (adjacency list) cho BFS

// BFS tìm đường tăng luồng từ s đến t
// Trả về lượng luồng có thể tăng trên đường tìm được
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1); // -1 nghĩa là nút chưa được thăm
    parent[s] = -2; // đánh dấu nút nguồn là đã thăm, -2 để phân biệt với các nút khác

    queue<pair<int, int>> q;
    q.push({s, INF}); // bắt đầu từ nguồn với luồng vô hạn

    while (!q.empty()) {
        int cur = q.front().first;   // nút hiện tại
        int flow = q.front().second; // luồng tối đa đi tới cur
        q.pop();

        for (int next : adj[cur]) { // duyệt tất cả các nút kề
            // Nếu chưa thăm và còn dung lượng trên cạnh
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur; // đánh dấu cha của next là cur
                int new_flow = min(flow, capacity[cur][next]); // luồng khả dụng mới
                if (next == t) // nếu tới đích, trả về luồng
                    return new_flow;
                q.push({next, new_flow}); // thêm next vào queue
            }
        }
    }

    return 0; // không còn đường tăng luồng nào
}

// Hàm chính tính luồng cực đại từ s đến t
int maxflow(int s, int t) {
    int flow = 0; // tổng luồng cực đại
    vector<int> parent(n);
    int new_flow;

    // Lặp cho tới khi BFS không còn đường tăng luồng nào
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow; // cộng luồng tìm được vào tổng luồng

        // Cập nhật lại dung lượng trên đường vừa tìm được
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow; // trừ luồng đã dùng
            capacity[cur][prev] += new_flow; // thêm luồng ngược (residual)
            cur = prev;
        }
    }

    return flow; // trả về luồng cực đại
}
