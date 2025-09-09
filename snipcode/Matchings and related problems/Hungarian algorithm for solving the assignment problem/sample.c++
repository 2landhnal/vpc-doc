#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<int>> A(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            fin >> A[i][j];

    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<bool> used(m + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1 = -1;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = A[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        // Restore augmenting path
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // Kết quả: ans[i] = cột ghép với hàng i
    vector<int> ans(n + 1);
    for (int j = 1; j <= m; ++j)
        ans[p[j]] = j;

    // Tổng chi phí tối thiểu
    int cost = -v[0];

    cout << "Minimum cost: " << cost << "\n";
    cout << "Assignments (row -> column):\n";
    for (int i = 1; i <= n; ++i)
        cout << i << " -> " << ans[i] << "\n";

    fin.close();
    return 0;
}
