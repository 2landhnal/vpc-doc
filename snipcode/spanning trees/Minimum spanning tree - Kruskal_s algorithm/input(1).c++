#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int main() {
    int n, m;
    cin >> n >> m; // số đỉnh, số cạnh
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        // Nếu input đánh số từ 1..n thì nhớ trừ đi 1:
        // edges[i].u--, edges[i].v--;
    }

    // Kruskal cơ bản với tree_id
    vector<int> tree_id(n);
    for (int i = 0; i < n; i++) tree_id[i] = i;

    sort(edges.begin(), edges.end());

    int cost = 0;
    vector<Edge> result;

    for (Edge e : edges) {
        if (tree_id[e.u] != tree_id[e.v]) {
            cost += e.weight;
            result.push_back(e);

            int old_id = tree_id[e.u], new_id = tree_id[e.v];
            for (int i = 0; i < n; i++) {
                if (tree_id[i] == old_id)
                    tree_id[i] = new_id;
            }
        }
    }

    cout << "MST cost = " << cost << "\n";
    cout << "Edges in MST:\n";
    for (auto e : result) {
        cout << e.u << " " << e.v << " (" << e.weight << ")\n";
    }
}
