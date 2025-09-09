int main() {
    int n;
    vector<vector<int>> g(n, vector<int>(n));
    // g là ma trận kề (adjacency matrix) lưu số cạnh giữa 2 đỉnh.
    // n là số đỉnh trong đồ thị.
    // Ví dụ: g[u][v] = 2 nghĩa là có 2 cạnh song song giữa u và v.

    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j]; 
            // tính bậc của đỉnh i (tổng số cạnh nối với i)
    }

    int first = 0;
    while (first < n && !deg[first])
        ++first;
    if (first == n) {
        cout << -1;
        return 0;
    }
    // tìm một đỉnh có bậc > 0 để làm điểm bắt đầu.
    // nếu tất cả deg = 0 => đồ thị rỗng => không có đường Euler.

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) { 
            // nếu bậc lẻ
            if (v1 == -1)
                v1 = i;   // đỉnh lẻ thứ 1
            else if (v2 == -1)
                v2 = i;   // đỉnh lẻ thứ 2
            else
                bad = true; // nhiều hơn 2 đỉnh bậc lẻ => không tồn tại Euler path
        }
    }

    if (v1 != -1)
        ++g[v1][v2], ++g[v2][v1];
    // nếu tồn tại 2 đỉnh bậc lẻ, thêm 1 cạnh giả nối chúng
    // => biến bài toán Euler path thành Euler cycle.

    stack<int> st;
    st.push(first);
    vector<int> res;
    // res sẽ chứa kết quả đường đi Euler.

    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i])
                break;
        if (i == n) {
            // không còn cạnh nào từ v
            res.push_back(v);
            st.pop();
        } else {
            // đi theo cạnh v-i
            --g[v][i];
            --g[i][v];
            st.push(i);
        }
    }
    // Đây là phần chính của Hierholzer’s algorithm:
    // lấy cạnh và đi sâu dần, khi hết đường thì quay lui, tạo thành đường Euler.

    if (v1 != -1) {
        // nếu ban đầu có 2 đỉnh bậc lẻ,
        // thì trong res hiện tại có thêm cạnh giả (v1-v2).
        // Đoạn code này cắt bỏ cạnh giả để lấy đúng Euler path ban đầu.
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    // kiểm tra lại: nếu vẫn còn cạnh chưa đi hết => đồ thị không Eulerian
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j])
                bad = true;
        }
    }

    if (bad) {
        cout << -1;
    } else {
        for (int x : res)
            cout << x << " ";
    }
}
