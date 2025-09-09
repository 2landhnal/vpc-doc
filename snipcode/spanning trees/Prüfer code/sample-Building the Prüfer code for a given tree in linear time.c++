vector<vector<int>> adj;   // adjacency list của cây
vector<int> parent;        // mảng cha của mỗi đỉnh (được xây dựng từ DFS)

// DFS để tính cha cho mỗi đỉnh (root tại n-1)
void dfs(int v) {
    for (int u : adj[v]) {
        if (u != parent[v]) {  // tránh đi ngược lại cha
            parent[u] = v;     // gán cha của u
            dfs(u);            // đệ quy xuống con
        }
    }
}

vector<int> pruefer_code() {
    int n = adj.size();
    parent.resize(n);

    // chọn root là đỉnh cuối cùng (n-1)
    parent[n-1] = -1; 
    dfs(n-1); // sau khi DFS, ta có mảng parent[]

    // tìm đỉnh lá có chỉ số nhỏ nhất
    int ptr = -1;
    vector<int> degree(n);
    for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size(); // tính bậc mỗi đỉnh
        if (degree[i] == 1 && ptr == -1)  // lấy lá đầu tiên
            ptr = i;
    }

    vector<int> code(n - 2); 
    int leaf = ptr;

    // Thuật toán sinh Prüfer code
    for (int i = 0; i < n - 2; i++) {
        int next = parent[leaf]; // cha của lá hiện tại
        code[i] = next;          // thêm cha vào Prüfer code

        // giảm bậc của cha (vì lá vừa bị "loại")
        if (--degree[next] == 1 && next < ptr) {
            // nếu cha vừa trở thành lá 
            // và có chỉ số nhỏ hơn ptr hiện tại → chọn nó
            leaf = next;
        } else {
            // nếu không, tăng ptr để tìm lá mới tiếp theo
            ptr++;
            while (degree[ptr] != 1) // bỏ qua các đỉnh không phải lá
                ptr++;
            leaf = ptr; // chọn lá mới
        }
    }

    return code; // trả về dãy Prüfer
}
