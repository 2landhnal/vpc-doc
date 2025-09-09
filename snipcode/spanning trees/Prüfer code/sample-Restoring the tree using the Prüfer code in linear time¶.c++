vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
    int n = code.size() + 2;  
    // Với cây n đỉnh thì Prüfer code có độ dài n-2
    // => số đỉnh = |code| + 2

    vector<int> degree(n, 1);  
    // Mỗi đỉnh bắt đầu với bậc 1 (giả sử là lá)
    // Sau đó sẽ tăng bậc dựa vào số lần xuất hiện trong code

    for (int i : code)
        degree[i]++;  
        // Mỗi khi i xuất hiện trong code thì nó có thêm một cạnh
        // => tăng bậc của i lên

    int ptr = 0;
    while (degree[ptr] != 1) 
        ptr++;  
    // ptr = chỉ số của đỉnh lá nhỏ nhất hiện tại (bậc = 1)

    int leaf = ptr;  
    // leaf sẽ giữ lá hiện tại được chọn để nối

    vector<pair<int, int>> edges;  
    // Danh sách cạnh kết quả (cây gốc khôi phục)

    // Duyệt từng giá trị v trong Prüfer code
    for (int v : code) {
        edges.emplace_back(leaf, v);  
        // Nối cạnh (lá hiện tại, v)

        if (--degree[v] == 1 && v < ptr) {
            // Giảm bậc v, nếu v trở thành lá và nhỏ hơn ptr
            // => chọn v làm lá mới
            leaf = v;
        } else {
            // Ngược lại: tăng ptr đến khi gặp đỉnh bậc = 1
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }

    edges.emplace_back(leaf, n-1);  
    // Cuối cùng còn đúng 2 đỉnh bậc 1 chưa nối
    // => nối chúng với nhau

    return edges;  
    // Trả về danh sách cạnh của cây
}
