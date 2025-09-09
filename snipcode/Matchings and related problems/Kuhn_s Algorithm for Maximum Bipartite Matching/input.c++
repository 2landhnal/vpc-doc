#include <bits/stdc++.h>
using namespace std;

int n, k; // n = số đỉnh tập 1, k = số đỉnh tập 2
vector<vector<int>> g; // g[v] = danh sách các đỉnh của tập 2 mà v kết nối
vector<int> mt;        // mt[to] = đỉnh của tập 1 ghép với to, -1 nếu chưa ghép
vector<bool> used;     // đánh dấu đỉnh đã duyệt trong DFS

// DFS tìm augmenting path từ đỉnh v
bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    // Đọc từ file input.txt
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }

    int m; // số cạnh
    fin >> n >> k >> m;
    g.assign(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;      // u ∈ [1,n], v ∈ [1,k]
        --u; --v;           // chuyển về 0-based
        g[u].push_back(v);
    }

    // Khởi tạo ghép cặp
    mt.assign(k, -1);
    vector<bool> used1(n, false);

    // Heuristic: thêm các ghép cặp tùy ý để giảm số DFS
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) {
            if (mt[to] == -1) {
                mt[to] = v;
                used1[v] = true;
                break;
            }
        }
    }

    // DFS cải thiện ghép cặp
    for (int v = 0; v < n; ++v) {
        if (used1[v]) continue; // đã được ghép trong heuristic
        used.assign(n, false);
        try_kuhn(v);
    }

    // In kết quả: các cặp (đỉnh tập 1, đỉnh tập 2)
    for (int i = 0; i < k; ++i)
        if (mt[i] != -1)
            printf("%d %d\n", mt[i] + 1, i + 1);

    fin.close();
    return 0;
}