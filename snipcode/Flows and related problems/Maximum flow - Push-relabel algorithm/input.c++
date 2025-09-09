#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

int n; // số đỉnh
vector<vector<int>> capacity, flow;
vector<int> height, excess, seen;
queue<int> excess_vertices;

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

void discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v);
            else 
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

int max_flow(int s, int t) {
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;

    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }

    seen.assign(n, 0);

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}

int main() {
    // Đọc từ bàn phím hoặc file
    // Ví dụ: input.txt có format:
    // n m
    // u1 v1 c1
    // u2 v2 c2
    // ...
    int m;
    cin >> n >> m;
    capacity.assign(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c; // u, v: 0-indexed
        capacity[u][v] = c;
    }

    int s, t;
    cin >> s >> t; // nguồn và đích

    cout << "Max flow: " << max_flow(s, t) << "\n";
    return 0;
}
