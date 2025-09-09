#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b, cost;
};

int n, m, v;
vector<Edge> edges;
const int INF = 1000000000;

void solve() {
    vector<int> d(n, INF);
    d[v] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (Edge e : edges) {
            if (d[e.a] < INF) {
                d[e.b] = min(d[e.b], d[e.a] + e.cost);
            }
        }
    }

    // In kết quả khoảng cách
    for (int i = 0; i < n; i++) {
        if (d[i] == INF)
            cout << "INF ";
        else
            cout << d[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Đọc số đỉnh, số cạnh, và đỉnh nguồn
    cin >> n >> m >> v;

    // Đọc danh sách các cạnh
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].cost;
    }

    solve();
    return 0;
}
