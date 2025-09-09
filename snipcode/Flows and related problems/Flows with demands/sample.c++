#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to;
    long long cap, flow;
};

struct MaxFlow {
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    queue<int> q;

    MaxFlow(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int from, int to, long long cap) {
        edges.push_back({from, to, cap, 0});
        edges.push_back({to, from, 0, 0});
        adj[from].push_back(edges.size() - 2);
        adj[to].push_back(edges.size() - 1);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q = queue<int>();
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int id : adj[v]) {
                Edge &e = edges[id];
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, int t, long long pushed) {
        if (!pushed) return 0;
        if (v == t) return pushed;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            Edge &e = edges[id];
            if (level[v] + 1 != level[e.to] || e.flow == e.cap) continue;
            long long tr = dfs(e.to, t, min(pushed, e.cap - e.flow));
            if (tr == 0) continue;
            e.flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int,int,long long,long long>> edges; // u, v, demand, capacity
    vector<long long> balance(n, 0);

    for (int i = 0; i < m; i++) {
        int u,v; long long d,c;
        cin >> u >> v >> d >> c; // demand, capacity
        u--; v--; // 0-indexed
        edges.push_back({u,v,d,c});
        balance[u] -= d; // subtract demand from from-node
        balance[v] += d; // add demand to to-node
    }

    int S = n, T = n+1;
    MaxFlow mf(n+2);

    // add edges with adjusted capacity
    for (auto [u,v,d,c] : edges) {
        mf.add_edge(u,v,c-d); // capacity minus demand
    }

    long long total_demand = 0;
    for (int i = 0; i < n; i++) {
        if (balance[i] > 0) { // needs inflow
            mf.add_edge(S,i,balance[i]);
            total_demand += balance[i];
        } else if (balance[i] < 0) { // excess outflow
            mf.add_edge(i,T,-balance[i]);
        }
    }

    long long flow = mf.max_flow(S,T);
    if (flow == total_demand) {
        cout << "Feasible flow exists\n";
        cout << "Flow on original edges:\n";
        for (int i = 0; i < m; i++) {
            Edge &e = mf.edges[2*i];
            cout << "Edge " << i+1 << ": " << e.flow + get<2>(edges[i]) << "\n";
        }
    } else {
        cout << "No feasible flow exists\n";
    }
}
