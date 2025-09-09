#include <bits/stdc++.h>
using namespace std;

int n, m;                        // số đỉnh, số cạnh
vector<vector<int>> adj;         // danh sách kề
vector<bool> used;               // đánh dấu đã thăm
vector<int> comp;                // lưu thành phần liên thông

void dfs(int v) {
    stack<int> st;
    st.push(v);

    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        if (!used[curr]) {
            used[curr] = true;
            comp.push_back(curr);
            for (int i = (int)adj[curr].size() - 1; i >= 0; i--) {
                st.push(adj[curr][i]);
            }
        }
    }
}

void find_comps() {
    fill(used.begin(), used.end(), false);
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            comp.clear();
            dfs(v);
            cout << "Component:";
            for (int u : comp)
                cout << ' ' << u;
            cout << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---- đọc input ----
    cin >> n >> m;              // số đỉnh, số cạnh
    adj.assign(n, {});          // khởi tạo danh sách kề
    used.assign(n, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;          // cạnh (u, v)
        adj[u].push_back(v);
        adj[v].push_back(u);    // bỏ dòng này nếu đồ thị có hướng
    }

    // ---- tìm các thành phần liên thông ----
    find_comps();

    return 0;
}
