#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
using namespace std;

const int INF = 1000000000; // giá trị vô cùng (dùng để khởi tạo khoảng cách)
vector<vector<pair<int, int>>> adj; 
// adj[u] = danh sách các cạnh kề của đỉnh u
// mỗi phần tử là (v, w) nghĩa là có cạnh u -> v với trọng số w

// Hàm Dijkstra: tìm đường đi ngắn nhất từ đỉnh s đến các đỉnh khác
void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();   // số đỉnh trong đồ thị
    d.assign(n, INF);     // khởi tạo khoảng cách: tất cả vô cùng
    p.assign(n, -1);      // khởi tạo mảng cha: chưa có đỉnh trước

    d[s] = 0; // khoảng cách từ s đến s bằng 0
    set<pair<int, int>> q; 
    // set (khoảng cách, đỉnh) – dùng để lấy đỉnh có khoảng cách nhỏ nhất
    q.insert({0, s});

    while (!q.empty()) {
        // lấy đỉnh v có d[v] nhỏ nhất trong tập q
        int v = q.begin()->second;
        q.erase(q.begin());

        // duyệt tất cả cạnh (v -> to) có trọng số len
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            // nếu tìm thấy đường đi ngắn hơn tới to qua v
            if (d[v] + len < d[to]) {
                // xóa giá trị cũ (nếu tồn tại) trong set
                q.erase({d[to], to});

                // cập nhật khoảng cách và cha
                d[to] = d[v] + len;
                p[to] = v;

                // chèn giá trị mới vào set
                q.insert({d[to], to});
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    // Đọc số đỉnh, số cạnh, và đỉnh nguồn
    cin >> n >> m;

    // Đọc danh sách các cạnh
    adj.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> adj[i]r.a >> adj[i].b >> adj[i].cost;
    }

    dijkstra(m);
    return 0;
}
