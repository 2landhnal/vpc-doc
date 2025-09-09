int n; // số đỉnh trong cây
vector<vector<int>> adj; // danh sách kề của cây

int block_size, block_cnt; // kích thước block và số block trong Euler tour
vector<int> first_visit;    // first_visit[v] = lần đầu tiên đỉnh v xuất hiện trong Euler tour
vector<int> euler_tour;     // Euler tour của cây
vector<int> height;         // chiều cao của mỗi đỉnh trong cây
vector<int> log_2;          // log_2[i] = floor(log2(i))
vector<vector<int>> st;     // sparse table cho block-level RMQ
vector<vector<vector<int>>> blocks; // RMQ cho mỗi block nhỏ (block size <= log n / 2)
vector<int> block_mask;     // mã hóa mỗi block theo +/-1 để RMQ O(1)

// DFS xây dựng Euler tour và height
void dfs(int v, int p, int h) {
    first_visit[v] = euler_tour.size();
    euler_tour.push_back(v);
    height[v] = h;

    for (int u : adj[v]) {
        if (u == p) continue;
        dfs(u, v, h + 1);
        euler_tour.push_back(v); // quay trở lại đỉnh v sau khi duyệt con u
    }
}

// So sánh hai chỉ số trong Euler tour theo height
int min_by_h(int i, int j) {
    return height[euler_tour[i]] < height[euler_tour[j]] ? i : j;
}

void precompute_lca(int root) {
    // 1. Euler tour & first visit
    first_visit.assign(n, -1);
    height.assign(n, 0);
    euler_tour.reserve(2 * n);
    dfs(root, -1, 0);

    int m = euler_tour.size();

    // 2. Precompute log2 cho sparse table
    log_2.reserve(m + 1);
    log_2.push_back(-1);
    for (int i = 1; i <= m; i++)
        log_2.push_back(log_2[i / 2] + 1);

    // 3. Chia Euler tour thành các block
    block_size = max(1, log_2[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;

    // 4. Build sparse table cho block-level
    st.assign(block_cnt, vector<int>(log_2[block_cnt] + 1));
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size) j = 0, b++;
        if (j == 0 || min_by_h(i, st[b][0]) == i)
            st[b][0] = i; // lưu chỉ số min trong block
    }
    for (int l = 1; l <= log_2[block_cnt]; l++) {
        for (int i = 0; i < block_cnt; i++) {
            int ni = i + (1 << (l - 1));
            if (ni >= block_cnt)
                st[i][l] = st[i][l-1];
            else
                st[i][l] = min_by_h(st[i][l-1], st[ni][l-1]);
        }
    }

    // 5. Precompute mask cho từng block (biểu diễn pattern +/-1)
    block_mask.assign(block_cnt, 0);
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size) j = 0, b++;
        if (j > 0 && (i >= m || min_by_h(i - 1, i) == i - 1))
            block_mask[b] += 1 << (j - 1);
    }

    // 6. Precompute RMQ cho mỗi block duy nhất
    int possibilities = 1 << (block_size - 1);
    blocks.resize(possibilities);
    for (int b = 0; b < block_cnt; b++) {
        int mask = block_mask[b];
        if (!blocks[mask].empty()) continue; // đã tính
        blocks[mask].assign(block_size, vector<int>(block_size));
        for (int l = 0; l < block_size; l++) {
            blocks[mask][l][l] = l;
            for (int r = l + 1; r < block_size; r++) {
                blocks[mask][l][r] = blocks[mask][l][r - 1];
                if (b * block_size + r < m)
                    blocks[mask][l][r] = min_by_h(
                        b * block_size + blocks[mask][l][r],
                        b * block_size + r
                    ) - b * block_size;
            }
        }
    }
}

// LCA trong một block
int lca_in_block(int b, int l, int r) {
    return blocks[block_mask[b]][l][r] + b * block_size;
}

// Trả về LCA của hai đỉnh v và u
int lca(int v, int u) {
    int l = first_visit[v];
    int r = first_visit[u];
    if (l > r) swap(l, r);

    int bl = l / block_size;
    int br = r / block_size;

    if (bl == br) // cùng block
        return euler_tour[lca_in_block(bl, l % block_size, r % block_size)];

    // lấy min trong hai block biên
    int ans1 = lca_in_block(bl, l % block_size, block_size - 1);
    int ans2 = lca_in_block(br, 0, r % block_size);
    int ans = min_by_h(ans1, ans2);

    // lấy min trong các block giữa (sử dụng sparse table)
    if (bl + 1 < br) {
        int lg = log_2[br - bl - 1];
        int ans3 = st[bl+1][lg];
        int ans4 = st[br - (1 << lg)][lg];
        ans = min_by_h(ans, min_by_h(ans3, ans4));
    }

    return euler_tour[ans];
}
