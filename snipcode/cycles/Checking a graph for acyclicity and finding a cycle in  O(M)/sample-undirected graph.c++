int n;                          // số đỉnh trong đồ thị
vector<vector<int>> adj;        // danh sách kề (adjacency list)
vector<bool> visited;           // đánh dấu đỉnh đã thăm
vector<int> parent;             // mảng lưu cha của mỗi đỉnh để khôi phục chu trình
int cycle_start, cycle_end;     // lưu điểm bắt đầu và kết thúc của chu trình

// DFS tìm chu trình trong đồ thị vô hướng
bool dfs(int v, int par) { // v: đỉnh hiện tại, par: cha của v trong cây DFS
    visited[v] = true;     // đánh dấu v đã thăm
    for (int u : adj[v]) { // duyệt các đỉnh kề u của v
        if (u == par) continue;  // bỏ qua cạnh ngược lại cha (tránh false positive)

        if (visited[u]) {
            // gặp một đỉnh đã được thăm mà không phải cha của v → phát hiện chu trình
            cycle_end = v;       // đánh dấu v là điểm cuối
            cycle_start = u;     // đánh dấu u là điểm đầu
            return true;         // báo có chu trình
        }

        parent[u] = v;           // lưu cha của u
        if (dfs(u, parent[u]))   // tiếp tục DFS từ u
            return true;         // nếu tìm được chu trình thì thoát
    }
    return false; // không có chu trình nào qua v
}

void find_cycle() {
    visited.assign(n, false); // khởi tạo tất cả chưa thăm
    parent.assign(n, -1);     // chưa có cha
    cycle_start = -1;         // mặc định chưa tìm thấy chu trình

    // duyệt toàn bộ đồ thị (phòng khi đồ thị không liên thông)
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
            break; // nếu đã tìm thấy chu trình thì dừng
    }

    if (cycle_start == -1) {
        cout << "Acyclic" << endl; // không tìm thấy chu trình
    } else {
        // khôi phục lại chu trình từ cycle_start → cycle_end
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start); // đóng chu trình lại

        cout << "Cycle found: ";
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
}
