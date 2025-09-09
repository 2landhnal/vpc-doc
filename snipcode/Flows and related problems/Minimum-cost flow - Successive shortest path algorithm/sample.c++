struct Edge
{
    int from, to, capacity, cost;
};

// adjacency list, chi phí và công suất mỗi cạnh
vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

// Tìm đường đi ngắn nhất từ v0 đến tất cả các đỉnh theo chi phí trên residual graph
// Dùng SPFA (có thể dùng Dijkstra nếu không có cạnh âm)
void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);       // khoảng cách từ v0
    d[v0] = 0;              // đỉnh nguồn = 0
    vector<bool> inq(n, false); // kiểm tra đỉnh có trong queue hay không
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);        // lưu cha để hồi ngược đường đi

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            // chỉ xét cạnh còn dư
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v]; // cập nhật khoảng cách
                p[v] = u;                 // lưu cha
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);            // thêm vào queue nếu chưa có
                }
            }
        }
    }
}

// Hàm Min-Cost Flow
// N = số đỉnh, edges = list cạnh, K = luồng cần gửi, s = source, t = sink
int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    // khởi tạo adjacency, cost, capacity
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from); // thêm cạnh ngược cho residual graph
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost; // cạnh ngược = -cost
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;  // tổng luồng đã gửi
    int total_cost = 0;  // tổng chi phí
    vector<int> d, p; // khoảng cách và parent

    while (flow < K) {
        shortest_paths(N, s, d, p); // tìm đường đi ngắn nhất theo chi phí
        if (d[t] == INF) // không còn đường đi khả thi
            break;

        // tìm luồng tối đa có thể gửi trên đường đi vừa tìm
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]); // hạn chế bởi công suất cạnh nhỏ nhất
            cur = p[cur];
        }

        // áp dụng luồng f lên đường đi
        flow += f;
        total_cost += f * d[t]; // chi phí = f * tổng chi phí đường đi
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f; // giảm residual
            capacity[cur][p[cur]] += f; // tăng cạnh ngược
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1; // không thể gửi đủ K luồng
    else
        return total_cost;
}
