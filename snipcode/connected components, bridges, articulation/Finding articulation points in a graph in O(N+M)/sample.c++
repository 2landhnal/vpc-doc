int n; // số lượng đỉnh trong đồ thị
vector<vector<int>> adj; // danh sách kề của đồ thị (graph adjacency list)

vector<bool> visited; // đánh dấu đỉnh đã được duyệt trong DFS hay chưa
vector<int> tin, low; 
// tin[v]: thời điểm (timestamp) khi DFS lần đầu tiên thăm đỉnh v
// low[v]: thời điểm nhỏ nhất có thể tới được từ v (bao gồm back-edge)

int timer; // biến toàn cục để đếm thời gian duyệt DFS

// Hàm DFS tìm articulation points
void dfs(int v, int p = -1) {
    visited[v] = true; 
    tin[v] = low[v] = timer++; 
    // khởi tạo thời điểm thăm và low bằng timer hiện tại
    int children = 0; // số con trực tiếp của v trong DFS tree
    
    // duyệt tất cả đỉnh kề với v
    for (int to : adj[v]) {
        if (to == p) continue; // bỏ qua cạnh ngược về cha
        
        if (visited[to]) {
            // Nếu "to" đã được thăm trước đó => tồn tại back-edge
            low[v] = min(low[v], tin[to]); 
        } else {
            // Nếu "to" chưa thăm thì tiếp tục DFS
            dfs(to, v);
            
            // Sau khi DFS xong, cập nhật low[v]
            low[v] = min(low[v], low[to]);
            
            // Điều kiện để v là articulation point (không phải root):
            // Nếu không có đường back-edge nào từ subtree "to" quay về tổ tiên của v
            if (low[to] >= tin[v] && p != -1)
                IS_CUTPOINT(v); // v là articulation point
            
            ++children; // tăng số con trực tiếp trong DFS tree
        }
    }
    
    // Trường hợp đặc biệt: nếu v là root của DFS tree
    // Root chỉ là articulation point nếu có >= 2 nhánh con
    if (p == -1 && children > 1)
        IS_CUTPOINT(v);
}

// Hàm khởi động tìm articulation points
void find_cutpoints() {
    timer = 0; 
    visited.assign(n, false); 
    tin.assign(n, -1); 
    low.assign(n, -1); 
    
    // duyệt toàn bộ các đỉnh (đề phòng đồ thị rời rạc)
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i); 
    }
}
