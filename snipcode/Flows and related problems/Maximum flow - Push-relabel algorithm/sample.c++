const int inf = 1000000000;

int n; // số đỉnh trong mạng luồng
vector<vector<int>> capacity, flow; // capacity[u][v]: công suất của cạnh u->v, flow[u][v]: dòng hiện tại
vector<int> height, excess, seen; // height[u]: chiều cao của u, excess[u]: lượng dòng dư tại u, seen[u]: chỉ số cạnh đang xét để push
queue<int> excess_vertices; // danh sách các đỉnh có dòng dư > 0 (ngoại trừ s và t)

// Đẩy dòng từ u sang v
void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]); // lượng có thể đẩy
    flow[u][v] += d;    // tăng dòng u->v
    flow[v][u] -= d;    // cập nhật dòng ngược (residual)
    excess[u] -= d;     // giảm dòng dư tại u
    excess[v] += d;     // tăng dòng dư tại v

    // nếu trước đó excess[v] = 0 và bây giờ >0, thêm v vào hàng chờ
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

// Nâng cao chiều cao của u
void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0) // chỉ xét các cạnh còn dư
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1; // chiều cao mới của u phải lớn hơn tất cả các đỉnh kề còn dư
}

// Xử lý đỉnh u có dòng dư
void discharge(int u) {
    while (excess[u] > 0) { // còn dòng dư thì tiếp tục xử lý
        if (seen[u] < n) { // còn đỉnh kề để thử push
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v); // đẩy nếu có dư và u cao hơn v
            else 
                seen[u]++; // sang cạnh kế tiếp
        } else {
            relabel(u); // nếu không thể push sang đâu được, nâng chiều cao
            seen[u] = 0; // bắt đầu xét lại từ cạnh đầu
        }
    }
}

// Hàm tính max flow từ s đến t
int max_flow(int s, int t) {
    height.assign(n, 0); // khởi tạo chiều cao
    height[s] = n;        // chiều cao nguồn = n (theo thuật toán Push–Relabel)
    flow.assign(n, vector<int>(n, 0)); // khởi tạo dòng ban đầu = 0
    excess.assign(n, 0); 
    excess[s] = inf; // ban đầu, đẩy tất cả dòng từ nguồn

    // push tất cả dòng từ s sang các đỉnh kề
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }

    seen.assign(n, 0); // khởi tạo chỉ số cạnh xét để push

    // xử lý các đỉnh có dòng dư (ngoại trừ s và t)
    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    // tính tổng dòng đi vào đích t
    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    return max_flow;
}
