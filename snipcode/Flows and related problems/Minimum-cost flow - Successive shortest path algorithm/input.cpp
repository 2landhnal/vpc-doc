#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;

struct Edge {
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;
const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int s, int t) {
    int K = 100000000;
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0, total_cost = 0;
    vector<int> d, p;

    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        flow += f;
        total_cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return total_cost;
}

int main() {
    int N, M, K, s, t;
    cout << "Enter number of nodes, edges, desired flow K, source, sink:\n";
    cin >> N >> M >> s >> t;

    vector<Edge> edges(M);
    cout << "Enter each edge as: from to capacity cost\n";
    for (int i = 0; i < M; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].capacity >> edges[i].cost;
    }

    int result = min_cost_flow(N, edges, s, t);
    if (result == -1)
        cout << "Cannot send desired flow K\n";
    else
        cout << "Minimum cost to send flow " << K << " is " << result << "\n";

    return 0;
}
