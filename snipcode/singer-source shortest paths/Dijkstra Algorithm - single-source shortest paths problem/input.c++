#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.assign(n, {});
    int start;
    cin >> start;
    start--; // chuyển về chỉ số 0-based

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({b, w});
        // Nếu đồ thị vô hướng thì thêm dòng sau:
        // adj[b].push_back({a, w});
    }

    vector<int> d, p;
    dijkstra(start, d, p);

// ví dụ: in đường đi từ start đến tất cả các đỉnh
    for (int t = 0; t < n; t++) {
        if (d[t] == INF) {
            cout << "No path to " << t+1 << "\n";
        } else {
            cout << "Dist to " << t+1 << " = " << d[t] << ", Path: ";
            vector<int> path = restore_path(start, t, p);
            for (int v : path) cout << v+1 << " ";
            cout << "\n";
        }
    }
}