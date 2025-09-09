// Định nghĩa
// s-t cut: Chia tập các đỉnh của đồ thị thành 2 tập:
// Tập 1 chứa nguồn s
// Tập 2 chứa cống t
// Capacity của s-t cut: Tổng dung lượng của các cạnh đi từ tập chứa s sang tập chứa t.

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, m; // số đỉnh, số cạnh
vector<vector<int>> capacity, adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INF});

    while(!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int next : adj[cur]) {
            if(parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if(next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while(new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while(cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

// DFS từ nguồn s trong residual graph để xác định tập S của minimum cut
void dfs(int u, vector<bool>& visited) {
    visited[u] = true;
    for(int v : adj[u]) {
        if(capacity[u][v] > 0 && !visited[v])
            dfs(v, visited);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m; // số đỉnh và số cạnh
    adj.assign(n, vector<int>());
    capacity.assign(n, vector<int>(n, 0));

    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c; // 0-indexed vertices
        adj[u].push_back(v);
        adj[v].push_back(u); // thêm cả reverse edge cho residual graph
        capacity[u][v] = c;
    }

    int s = 0, t = n-1; // giả sử s=0, t=n-1
    int flow = maxflow(s, t);
    cout << "Maximum flow: " << flow << "\n";

    // tìm tập S trong minimum cut
    vector<bool> visited(n, false);
    dfs(s, visited);

    cout << "Edges in minimum cut:\n";
    for(int u = 0; u < n; u++) {
        for(int v : adj[u]) {
            if(visited[u] && !visited[v] && capacity[u][v] == 0) {
                cout << u << " -> " << v << "\n";
            }
        }
    }

    return 0;
}
