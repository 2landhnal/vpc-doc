int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // đồ thị có hướng
    }

    vector<vector<int>> components, adj_cond;
    strongly_connected_components(adj, components, adj_cond);

    cout << components.size() << "\n";
    for (auto &comp : components) {
        for (int v : comp) cout << v << " ";
        cout << "\n";
    }
}