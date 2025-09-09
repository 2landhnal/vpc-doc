#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<int> parent, rnk;

void make_set(int v) {
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        // nếu input 1-based thì trừ đi 1 để về 0-based
        edges[i].u--;
        edges[i].v--;
    }

    parent.resize(n);
    rnk.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i);

    sort(edges.begin(), edges.end());

    int cost = 0;
    vector<Edge> result;
    for (Edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v);
        }
    }

    // In kết quả
    cout << "MST cost = " << cost << "\n";
    for (auto &e : result) {
        cout << e.u + 1 << " " << e.v + 1 << "\n"; // in lại về 1-based
    }
}
