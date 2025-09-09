// adj[u] chứa các node kề (con) của node u trong cây
vector<vector<int>> adj;

// queries[u] chứa các node mà ta cần tính LCA với node u
vector<vector<int>> queries;

// ancestor[v] lưu ancestor hiện tại của tập hợp DSU mà node v thuộc về
vector<int> ancestor;

// visited[v] đánh dấu xem node v đã được duyệt DFS chưa
vector<bool> visited;

// dfs thực hiện duyệt cây và tính LCA offline
void dfs(int v)
{
    visited[v] = true;        // đánh dấu node v đã được duyệt
    ancestor[v] = v;          // ban đầu ancestor của chính node v là node v

    // duyệt tất cả các con của node v
    for (int u : adj[v]) {
        if (!visited[u]) {    // nếu con u chưa được duyệt
            dfs(u);           // đệ quy DFS vào u

            // sau khi xử lý xong con u, gộp u vào tập hợp của v
            union_sets(v, u);

            // cập nhật ancestor của tập hợp mới sau khi gộp
            ancestor[find_set(v)] = v;
        }
    }

    // kiểm tra tất cả các truy vấn liên quan đến node v
    for (int other_node : queries[v]) {
        if (visited[other_node]) {
            // nếu node kia đã được duyệt, LCA là ancestor của tập hợp DSU chứa node đó
            cout << "LCA of " << v << " and " << other_node
                 << " is " << ancestor[find_set(other_node)] << ".\n";
        }
    }
}

// hàm chính để tính tất cả LCA offline
void compute_LCAs() {
    // khởi tạo n, adj, DSU (parent, rank)
    // ví dụ: mỗi truy vấn (u, v):
    // queries[u].push_back(v);
    // queries[v].push_back(u);

    ancestor.resize(n);          // khởi tạo mảng ancestor
    visited.assign(n, false);    // đánh dấu tất cả node chưa duyệt
    dfs(0);                      // bắt đầu DFS từ root (giả sử root = 0)
}
