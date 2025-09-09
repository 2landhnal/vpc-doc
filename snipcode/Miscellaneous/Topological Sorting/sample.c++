int n; // số đỉnh của đồ thị
vector<vector<int>> adj; // danh sách kề của đồ thị: adj[v] = các đỉnh kề từ v
vector<bool> visited;    // đánh dấu các đỉnh đã được thăm
vector<int> ans;         // danh sách kết quả sắp xếp topo

// DFS từ đỉnh v
void dfs(int v) {
    visited[v] = true;              // đánh dấu v đã thăm
    for (int u : adj[v]) {          // duyệt tất cả các đỉnh kề u từ v
        if (!visited[u]) {          // nếu u chưa thăm
            dfs(u);                 // đệ quy DFS từ u
        }
    }
    ans.push_back(v);               // khi hoàn thành DFS từ v, thêm v vào danh sách
    // Lưu ý: thêm sau khi thăm xong tất cả các đỉnh kề => đảm bảo các phụ thuộc của v được thêm trước
}

// Hàm thực hiện sắp xếp topo
void topological_sort() {
    visited.assign(n, false);       // khởi tạo mảng visited = false
    ans.clear();                    // xóa danh sách kết quả cũ
    for (int i = 0; i < n; ++i) {  // duyệt tất cả các đỉnh
        if (!visited[i]) {          // nếu đỉnh i chưa thăm
            dfs(i);                 // chạy DFS từ i
        }
    }
    reverse(ans.begin(), ans.end()); // đảo ngược danh sách DFS hoàn thành để ra topological order
    // vì trong DFS, đỉnh được thêm sau các đỉnh phụ thuộc của nó, nên cần đảo ngược
}
