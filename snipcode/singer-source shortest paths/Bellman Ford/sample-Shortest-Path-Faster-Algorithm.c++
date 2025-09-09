const int INF = 1000000000;
vector<vector<pair<int, int>>> adj; // adj[u] = danh sách (v, w) các cạnh từ u → v trọng số w

// SPFA: trả về true nếu không có chu trình âm, false nếu có
bool spfa(int s, vector<int>& d) {
    int n = adj.size();
    d.assign(n, INF);          // khởi tạo khoảng cách
    vector<int> cnt(n, 0);     // cnt[i] = số lần đỉnh i được cập nhật
    vector<bool> inqueue(n, false); // đánh dấu đỉnh có đang trong hàng đợi hay không
    queue<int> q;

    d[s] = 0;
    q.push(s);
    inqueue[s] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        inqueue[v] = false;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;  // cập nhật khoảng cách
                if (!inqueue[to]) {
                    q.push(to);      // cho vào hàng đợi nếu chưa có
                    inqueue[to] = true;
                    cnt[to]++;       // tăng số lần cập nhật
                    if (cnt[to] > n)
                        return false;  // phát hiện chu trình âm
                }
            }
        }
    }
    return true; // không có chu trình âm
}
