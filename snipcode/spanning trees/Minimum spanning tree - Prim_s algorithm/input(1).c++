#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;  // số đỉnh và số cạnh

    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;   // đọc cạnh
        edges.push_back({u, v, w});
    }

    // Nếu muốn lưu theo adjacency list (cho Prim, Dijkstra,...):
    vector<vector<pair<int,int>>> adj(n + 1);
    for (auto &e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w}); // nếu là đồ thị vô hướng
    }

    // Kiểm tra đọc xong chưa
    cout << "Graph has " << n << " vertices and " << m << " edges\n";
    return 0;
}
