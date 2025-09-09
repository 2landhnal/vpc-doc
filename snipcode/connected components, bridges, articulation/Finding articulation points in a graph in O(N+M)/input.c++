int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_cutpoints();

    cout << "Articulation points:\n";
    for (int i = 1; i <= n; i++) {
        if (is_cutpoint[i]) cout << i << " ";
    }
    cout << "\n";
}