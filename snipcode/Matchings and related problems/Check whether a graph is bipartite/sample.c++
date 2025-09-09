int n;                        // số đỉnh của đồ thị
vector<vector<int>> adj;       // danh sách kề của đồ thị

vector<int> side(n, -1);      // mảng đánh dấu "phía" của mỗi đỉnh: -1 = chưa gán, 0 hoặc 1 = hai phía
bool is_bipartite = true;      // biến kiểm tra xem đồ thị có phải bipartite không
queue<int> q;                  // hàng đợi để duyệt BFS

for (int st = 0; st < n; ++st) {       // duyệt tất cả các đỉnh (cần thiết nếu đồ thị không liên thông)
    if (side[st] == -1) {              // nếu đỉnh chưa được gán phía
        q.push(st);                     // bắt đầu BFS từ đỉnh st
        side[st] = 0;                   // gán đỉnh này vào phía 0
        while (!q.empty()) {            // BFS bắt đầu
            int v = q.front();          // lấy đỉnh ở đầu hàng đợi
            q.pop();                    // loại bỏ đỉnh vừa lấy
            for (int u : adj[v]) {      // duyệt tất cả các đỉnh kề với v
                if (side[u] == -1) {    // nếu đỉnh u chưa được gán phía
                    side[u] = side[v] ^ 1;  // gán phía đối lập với v (0^1=1, 1^1=0)
                    q.push(u);              // thêm u vào hàng đợi để tiếp tục BFS
                } else {
                    // nếu u đã được gán phía, kiểm tra có vi phạm tính hai phía không
                    is_bipartite &= side[u] != side[v]; 
                    // nếu u và v cùng phía => is_bipartite = false
                }
            }
        }
    }
}

cout << (is_bipartite ? "YES" : "NO") << endl;  
// in ra YES nếu đồ thị là bipartite, NO nếu không phải
