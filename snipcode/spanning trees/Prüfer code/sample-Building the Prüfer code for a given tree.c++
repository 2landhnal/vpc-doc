vector<vector<int>> adj;  // adjacency list của cây (adj[i] chứa danh sách các đỉnh kề với i)

vector<int> pruefer_code() {
    int n = adj.size(); // số đỉnh của cây
    
    set<int> leafs;     // tập hợp các lá hiện tại (set để luôn lấy ra lá nhỏ nhất)
    vector<int> degree(n); // degree[i] = bậc của đỉnh i
    vector<bool> killed(n, false); // đánh dấu đỉnh đã bị "xóa" khỏi cây
    
    // Khởi tạo degree và tìm các lá ban đầu
    for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1)   // nếu đỉnh có bậc 1 => nó là lá
            leafs.insert(i);
    }

    vector<int> code(n - 2); // Prüfer code có độ dài n-2
    
    // Thuật toán sinh Prüfer code: lặp n-2 lần
    for (int i = 0; i < n - 2; i++) {
        // Lấy ra lá nhỏ nhất hiện tại
        int leaf = *leafs.begin();
        leafs.erase(leafs.begin());
        killed[leaf] = true; // "xóa" lá đó khỏi cây

        // Tìm đỉnh kề với lá đó (chỉ còn một đỉnh vì leaf có degree = 1)
        int v;
        for (int u : adj[leaf]) {
            if (!killed[u])   // tìm đỉnh chưa bị xóa
                v = u;
        }

        code[i] = v; // thêm đỉnh kề vào Prüfer code

        // Giảm bậc của đỉnh v vì lá leaf vừa bị xóa
        if (--degree[v] == 1) 
            leafs.insert(v); // nếu v trở thành lá thì thêm vào set
    }

    return code; // trả về dãy Prüfer code
}
