#include <bits/stdc++.h>
using namespace std;

const int INF = 1000 * 1000 * 1000;

// Hàm Assignment Problem
vector<int> assignment(vector<vector<int>> a) {
    int n = a.size();
    int m = n * 2 + 2;
    vector<vector<int>> f(m, vector<int>(m));
    int s = m - 2, t = m - 1;
    int cost = 0;

    while (true) {
        vector<int> dist(m, INF), p(m);
        vector<bool> inq(m, false);
        queue<int> q;
        dist[s] = 0;
        p[s] = -1;
        q.push(s);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            inq[v] = false;

            if (v == s) {
                for (int i = 0; i < n; ++i) {
                    if (f[s][i] == 0) {
                        dist[i] = 0;
                        p[i] = s;
                        if (!inq[i]) { q.push(i); inq[i] = true; }
                    }
                }
            } else if (v < n) {
                for (int j = n; j < n + n; ++j) {
                    if (f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n]) {
                        dist[j] = dist[v] + a[v][j - n];
                        p[j] = v;
                        if (!inq[j]) { q.push(j); inq[j] = true; }
                    }
                }
            } else {
                for (int j = 0; j < n; ++j) {
                    if (f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n]) {
                        dist[j] = dist[v] - a[j][v - n];
                        p[j] = v;
                        if (!inq[j]) { q.push(j); inq[j] = true; }
                    }
                }
            }
        }

        int curcost = INF;
        for (int i = n; i < n + n; ++i) {
            if (f[i][t] == 0 && dist[i] < curcost) {
                curcost = dist[i];
                p[t] = i;
            }
        }

        if (curcost == INF)
            break;

        cost += curcost;
        for (int cur = t; cur != -1; cur = p[cur]) {
            int prev = p[cur];
            if (prev != -1)
                f[cur][prev] = -(f[prev][cur] = 1);
        }
    }

    vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (f[i][j + n] == 1)
                answer[i] = j;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Đọc từ file "input.txt" hoặc từ bàn phím
    // Nếu dùng file, bỏ comment dòng sau:
    // freopen("input.txt", "r", stdin);

    int n;
    cin >> n; // số người / công việc
    vector<vector<int>> cost_matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> cost_matrix[i][j];

    vector<int> ans = assignment(cost_matrix);

    cout << "Assignment:\n";
    for (int i = 0; i < n; ++i)
        cout << "Person " << i << " -> Job " << ans[i] << "\n";

    return 0;
}
