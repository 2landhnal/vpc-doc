#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

int n; // số đỉnh
vector<vector<int>> capacity, flow;
vector<int> height, excess;

// Push luồng từ u sang v
void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

// Relabel: tăng height[u] để có thể push
void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

// Tìm tất cả đỉnh trung gian có luồng dư > 0 và height lớn nhất
vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < n; i++) {
        if (i != s && i != t && excess[i] > 0) {
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear();
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i);
        }
    }
    return max_height;
}

// Hàm tính max flow từ s -> t
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

    vector<int> current;
    while (!(current = find_max_height_vertices(s, t)).empty()) {
        for (int i : current) {
            bool pushed = false;
            for (int j = 0; j < n && excess[i]; j++) {
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
                    push(i, j);
                    pushed = true;
                }
            }
            if (!pushed) {
                relabel(i);
                break;
            }
        }
    }

    return excess[t];
}

int main() {
    // Đọc input
    int m, s, t;
    cin >> n >> m >> s >> t;
    capacity.assign(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c; // cạnh u -> v với dung lượng c
        capacity[u][v] = c;
    }

    int result = max_flow(s, t);
    cout << "Maximum flow: " << result << "\n";
    return 0;
}
