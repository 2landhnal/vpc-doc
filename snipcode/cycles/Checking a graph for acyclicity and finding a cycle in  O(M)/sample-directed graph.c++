int n;                          // số đỉnh
vector<vector<int>> adj;        // danh sách kề của đồ thị
vector<char> color;             // trạng thái của mỗi đỉnh: 0 = chưa thăm, 1 = đang thăm (trên stack), 2 = đã xong
vector<int> parent;             // mảng lưu cha để backtrack khi tìm được chu trình
int cycle_start, cycle_end;     // lưu lại điểm đầu và điểm cuối của chu trình

// DFS tìm chu trình
bool dfs(int v) {
    color[v] = 1; // đánh dấu v là "đang thăm" (trên đường đi hiện tại)

    for (int u : adj[v]) {      // duyệt tất cả đỉnh kề u của v
        if (color[u] == 0) {    // nếu u chưa được thăm
            parent[u] = v;      // gán cha của u là v
            if (dfs(u))         // tiếp tục DFS từ u
                return true;    // nếu phát hiện chu trình thì thoát sớm
        } else if (color[u] == 1) {
            // gặp lại một đỉnh "đang thăm" → có chu trình
            cycle_end = v;      // v là đỉnh cuối trên đường đi hiện tại
            cycle_start = u;    // u là đỉnh đầu chu trình (đã xuất hiện trước đó)
            return true;        // báo về có chu trình
        }
    }

    color[v] = 2; // đánh dấu v đã xong, không còn trên stack DFS
    return false;
}

// Hàm tìm chu trình trong đồ thị
void find_cycle() {
    color.assign(n, 0);      // ban đầu tất cả đỉnh đều chưa thăm
    parent.assign(n, -1);    // cha của mỗi đỉnh chưa xác định
    cycle_start = -1;        // mặc định chưa phát hiện chu trình

    // duyệt qua tất cả các đỉnh (đề phòng đồ thị không liên thông)
    for (int v = 0; v < n; v++) {
        if (color[v] == 0 && dfs(v)) // nếu v chưa thăm thì DFS
            break;                   // nếu tìm thấy chu trình thì thoát ngay
    }

    if (cycle_start == -1) {
        // không có chu trình
        cout << "Acyclic" << endl;
    } else {
        // khôi phục lại chu trình từ cycle_start đến cycle_end
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);  // đóng chu trình
        reverse(cycle.begin(), cycle.end()); // đảo lại để in đúng thứ tự

        // in chu trình tìm được
        cout << "Cycle found: ";
        for (int v : cycle)
            cout << v << " ";
        cout << endl;
    }
}
