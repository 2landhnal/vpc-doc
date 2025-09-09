const int inf = 1000000000;

int n; // số đỉnh trong đồ thị
vector<vector<int>> capacity, flow; // capacity[u][v] = dung lượng cạnh u->v; flow[u][v] = luồng hiện tại
vector<int> height, excess; // height[u] = độ cao của đỉnh, excess[u] = luồng dư tại đỉnh u

// Thực hiện push luồng từ u sang v
void push(int u, int v)
{
    // lượng luồng có thể push là min(excess[u], dung lượng còn lại trên cạnh)
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d; // tăng luồng đi từ u->v
    flow[v][u] -= d; // giảm luồng dư ngược v->u (residual)
    excess[u] -= d;   // trừ luồng đã push khỏi excess[u]
    excess[v] += d;   // cộng luồng nhận vào excess[v]
}

// Thực hiện relabel: tăng height[u] để có thể push được luồng
void relabel(int u)
{
    int d = inf;
    // tìm độ cao nhỏ nhất của các đỉnh láng giềng còn dư dung lượng
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1; // tăng height[u] lên hơn độ cao nhỏ nhất + 1
}

// Tìm tất cả các đỉnh có luồng dư > 0 và height lớn nhất
vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < n; i++) {
        if (i != s && i != t && excess[i] > 0) { // loại trừ source và sink
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear(); // tìm đỉnh cao nhất, bỏ các đỉnh thấp hơn
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i); // thêm đỉnh có height lớn nhất
        }
    }
    return max_height;
}

// Hàm chính tính max flow từ s -> t
int max_flow(int s, int t)
{
    height.assign(n, 0);     // khởi tạo height tất cả đỉnh = 0
    height[s] = n;            // source có height = n (luôn cao nhất)
    flow.assign(n, vector<int>(n, 0)); // khởi tạo luồng ban đầu = 0
    excess.assign(n, 0);      // khởi tạo luồng dư = 0
    excess[s] = inf;           // đặt excess tại source = vô cực
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);       // đẩy luồng từ source sang tất cả đỉnh kề
    }

    vector<int> current;
    // Lặp cho đến khi không còn đỉnh trung gian nào có luồng dư
    while (!(current = find_max_height_vertices(s, t)).empty()) {
        for (int i : current) {
            bool pushed = false;
            // Thử push sang tất cả đỉnh kề
            for (int j = 0; j < n && excess[i]; j++) {
                // push nếu còn dung lượng và height[i] == height[j] + 1
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
                    push(i, j);
                    pushed = true;
                }
            }
            // Nếu không push được, relabel để tăng height[i] và có thể push lần sau
            if (!pushed) {
                relabel(i);
                break;
            }
        }
    }

    return excess[t]; // luồng tối đa là luồng dư tại sink
}
