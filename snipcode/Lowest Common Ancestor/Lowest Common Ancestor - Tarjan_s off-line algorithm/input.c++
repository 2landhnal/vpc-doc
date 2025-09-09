#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<vector<int>> queries;
vector<int> ancestor, parent, rankDSU;
vector<bool> visited;

// DSU cơ bản
void make_set(int v) {
    parent[v] = v;
    rankDSU[v] = 0;
}

int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rankDSU[a] < rankDSU[b]) swap(a, b);
        parent[b] = a;
        if (rankDSU[a] == rankDSU[b]) rankDSU[a]++;
    }
}

// DFS Tarjan offline LCA
void dfs(int v)
{
    visited[v] = true;
    ancestor[v] = v;

    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
            union_sets(v, u);
            ancestor[find_set(v)] = v;
        }
    }

    for (int u : queries[v]) {
        if (visited[u]) {
            cout << "LCA of " << v << " and " << u 
                 << " is " << ancestor[find_set(u)] << endl;
        }
    }
}

int main() {
    int n, q;
    cin >> n >> q; // số node và số truy vấn

    adj.assign(n, {});
    queries.assign(n, {});
    parent.assign(n, 0);
    rankDSU.assign(n, 0);
    ancestor.assign(n, 0);
    visited.assign(n, false);

    // Khởi tạo DSU
    for (int i = 0; i < n; i++) make_set(i);

    // Input cây (n-1 cạnh)
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // giả sử input 1-indexed
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Input truy vấn
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        queries[u].push_back(v);
        queries[v].push_back(u);
    }

    // DFS từ root (giả sử node 0 là root)
    dfs(0);

    return 0;
}
