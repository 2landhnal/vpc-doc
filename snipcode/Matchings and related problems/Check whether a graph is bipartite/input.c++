#include <bits/stdc++.h>
using namespace std;

int main() {
    // Mở file input.txt để đọc dữ liệu
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }

    int n, m; // n = số đỉnh, m = số cạnh
    fin >> n >> m;

    vector<vector<int>> adj(n); // danh sách kề

    // Đọc các cạnh
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        --u; --v; // nếu file đếm đỉnh từ 1, chuyển về 0-based
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> side(n, -1); // -1 = chưa gán, 0 hoặc 1 = hai phía
    bool is_bipartite = true;
    queue<int> q;

    // Duyệt tất cả các thành phần liên thông
    for (int st = 0; st < n; ++st) {
        if (side[st] == -1) {
            q.push(st);
            side[st] = 0;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int u : adj[v]) {
                    if (side[u] == -1) {
                        side[u] = side[v] ^ 1; // gán phía đối lập
                        q.push(u);
                    } else {
                        is_bipartite &= side[u] != side[v]; // kiểm tra vi phạm
                    }
                }
            }
        }
    }

    cout << (is_bipartite ? "YES" : "NO") << endl;

    fin.close();
    return 0;
}
