vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
    int n = code.size() + 2;  
    // Với cây n đỉnh thì Prüfer code có độ dài n-2
    // => số đỉnh của cây là |code| + 2

    vector<int> degree(n, 1); 
    // Mỗi đỉnh ban đầu có bậc 1 (giả sử là lá)

    for (int i : code)
        degree[i]++;  
        // Mỗi khi đỉnh i xuất hiện trong Prüfer code,
        // nghĩa là có một cạnh nối đến nó
        // => tăng bậc của i lên

    set<int> leaves;
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1)  // tìm các lá thật sự
            leaves.insert(i); // tập hợp các lá (theo thứ tự tăng dần)
    }

    vector<pair<int, int>> edges; // danh sách cạnh kết quả

    // Duyệt qua từng số trong Prüfer code
    for (int v : code) {
        int leaf = *leaves.begin();   // lá nhỏ nhất hiện tại
        leaves.erase(leaves.begin()); // loại bỏ lá đó

        edges.emplace_back(leaf, v);  // nối lá với đỉnh v

        if (--degree[v] == 1)         // sau khi giảm bậc, nếu v trở thành lá
            leaves.insert(v);         // thêm v vào tập lá
    }

    // Cuối cùng còn đúng 2 lá chưa nối cạnh
    edges.emplace_back(*leaves.begin(), n-1);

    return edges; // trả về toàn bộ cạnh của cây
}
