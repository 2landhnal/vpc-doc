#include <bits/stdc++.h>
using namespace std;

// (copy lại code DSU + add_edge + merge_path đã giải thích ở trên)
// ... dán toàn bộ code init, find_2ecc, find_cc, make_root, merge_path, add_edge ...

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    init(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b; // đổi về 0-based
        add_edge(a, b);
        cout << bridges << "\n";
    }
}
