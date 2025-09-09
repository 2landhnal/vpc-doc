#include <bits/stdc++.h>
using namespace std;

int n, l;
vector<vector<int>> adj;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: n nodes, n-1 edges, then q queries
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // nếu input là 1-indexed
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0; // hoặc đọc root từ input nếu cần
    preprocess(root);

    int q;
    cin >> q; // số lượng query
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // nếu input 1-indexed
        cout << lca(u, v) + 1 << "\n"; // +1 nếu muốn output 1-indexed
    }

    return 0;
}