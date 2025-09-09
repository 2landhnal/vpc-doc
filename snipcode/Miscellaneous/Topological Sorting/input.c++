#include <bits/stdc++.h>
using namespace std;

int n, m; // n = số đỉnh, m = số cạnh
vector<vector<int>> adj; // danh sách kề
vector<bool> visited;
vector<int> ans;

// DFS từ đỉnh v
void dfs(int v) {
    visited[v] = true;              // đánh dấu đỉnh v đã thăm
    for (int u : adj[v]) {          // duyệt các đỉnh kề u
        if (!visited[u]) {
            dfs(u);                 // đệ quy DFS từ u
        }
    }
    ans.push_back(v);               // thêm v vào danh sách khi tất cả các đỉnh kề đã được thăm
}

// Hàm thực hiện sắp xếp topo
void topological_sort() {
    visited.assign(n, false);       // khởi tạo mảng visited
    ans.clear();                    // xóa danh sách kết quả cũ
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);                 // chạy DFS từ đỉnh chưa thăm
        }
    }
    reverse(ans.begin(), ans.end()); // đảo ngược danh sách DFS hoàn thành để ra topological order
}

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }

    fin >> n >> m;                   // đọc số đỉnh và số cạnh
    adj.assign(n, vector<int>());    // khởi tạo danh sách kề

    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;               // đọc cạnh u -> v
        --u; --v;                    // chuyển sang 0-based index
        adj[u].push_back(v);
    }

    fin.close();

    topological_sort();              // thực hiện sắp xếp topo

    cout << "Topological order:\n";
    for (int v : ans) {
        cout << v + 1 << " ";       // in kết quả 1-based index
    }
    cout << endl;

    return 0;
}
