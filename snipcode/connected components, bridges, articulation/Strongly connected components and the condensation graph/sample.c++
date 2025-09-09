vector<bool> visited; // mảng đánh dấu: đỉnh nào đã được thăm rồi thì true

// Hàm DFS: bắt đầu từ đỉnh v, đi sâu đệ quy
// Khi rời khỏi v (xử lý xong), ta thêm v vào vector output
void dfs(int v, vector<vector<int>> const& adj, vector<int> &output) {
    visited[v] = true; // đánh dấu đã thăm v
    for (auto u : adj[v]) // duyệt qua các đỉnh kề của v
        if (!visited[u])  // nếu chưa thăm u
            dfs(u, adj, output); // thì đệ quy DFS tiếp
    output.push_back(v); // sau khi đi hết, thêm v vào "thứ tự rời"
}

// adj: danh sách kề của đồ thị gốc G
// components: danh sách các thành phần liên thông mạnh (SCC)
// adj_cond: đồ thị ngưng kết (condensation graph) = G^SCC
void strongly_connected_components(vector<vector<int>> const& adj,
                                  vector<vector<int>> &components,
                                  vector<vector<int>> &adj_cond) {
    int n = adj.size();
    components.clear(), adj_cond.clear();

    vector<int> order; // chứa danh sách đỉnh theo thứ tự rời (exit time) sau DFS

    visited.assign(n, false);

    // ---- Bước 1: chạy DFS lần 1 trên G để lấy "thứ tự rời" ----
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    // ---- Bước 2: xây dựng đồ thị đảo cạnh G^T ----
    vector<vector<int>> adj_rev(n);
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            adj_rev[u].push_back(v); // đảo hướng cạnh v -> u thành u -> v

    // chuẩn bị cho DFS lần 2
    visited.assign(n, false);
    reverse(order.begin(), order.end()); // xét theo thứ tự giảm dần exit time

    vector<int> roots(n, 0); // roots[x] = đỉnh đại diện (root) của SCC chứa x

    // ---- Bước 3: DFS lần 2 trên G^T ----
    // Mỗi DFS sẽ tìm ra toàn bộ 1 SCC
    for (auto v : order)
        if (!visited[v]) {
            std::vector<int> component;
            dfs(v, adj_rev, component); // thu được 1 thành phần SCC
            components.push_back(component);

            // chọn 1 đỉnh nhỏ nhất trong SCC làm "root"
            int root = *min_element(begin(component), end(component));
            for (auto u : component)
                roots[u] = root;
        }

    // ---- Bước 4: Xây dựng đồ thị ngưng kết (condensation graph) ----
    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u]) // chỉ nối nếu u và v khác SCC
                adj_cond[roots[v]].push_back(roots[u]);
}
