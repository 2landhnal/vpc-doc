struct LCA {
    vector<int> height;    // Chiều cao của các nút trong cây
    vector<int> euler;     // Lưu thứ tự Euler tour của cây
    vector<int> first;     // Lưu chỉ số lần xuất hiện đầu tiên của nút trong Euler tour
    vector<int> segtree;   // Segment tree để tìm min height trong đoạn (RMQ)
    vector<bool> visited;  // Đánh dấu nút đã duyệt
    int n;

    // Constructor: khởi tạo và build LCA từ adjacency list
    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);       // Euler tour sẽ có kích thước tối đa 2*n-1
        visited.assign(n, false);
        dfs(adj, root);             // DFS để lấy Euler tour, chiều cao và first[]
        int m = euler.size();
        segtree.resize(m * 4);      // Segment tree có kích thước ~4*m
        build(1, 0, m - 1);         // Build segment tree dựa trên Euler tour
    }

    // DFS để tính chiều cao, Euler tour và first occurrence
    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;           // lưu chiều cao của nút hiện tại
        first[node] = euler.size(); // lưu chỉ số lần xuất hiện đầu tiên
        euler.push_back(node);      // thêm nút vào Euler tour

        for (auto to : adj[node]) { // duyệt tất cả con
            if (!visited[to]) {
                dfs(adj, to, h + 1); // DFS với chiều cao +1
                euler.push_back(node); // quay lại nút cha sau khi duyệt con
            }
        }
    }

    // Build segment tree trên Euler tour, lưu chỉ số nút có height nhỏ nhất trong mỗi đoạn
    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b]; // lá = nút Euler tại vị trí b
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);         // xây cây con trái
            build(node << 1 | 1, mid + 1, e); // xây cây con phải
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            // Lưu nút có chiều cao nhỏ hơn (gần gốc hơn)
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    // Query segment tree: tìm nút có chiều cao nhỏ nhất trong đoạn [L,R]
    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L) return -1; // đoạn ngoài phạm vi
        if (b >= L && e <= R) return segtree[node]; // đoạn nằm trong phạm vi
        int mid = (b + e) >> 1;
        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right; // chọn nút gần gốc hơn
    }

    // Tìm LCA của hai nút u và v
    int lca(int u, int v) {
        int left = first[u], right = first[v]; // lấy chỉ số xuất hiện đầu tiên trong Euler tour
        if (left > right) swap(left, right);
        return query(1, 0, euler.size() - 1, left, right); // min height trong Euler tour
    }
};
