// ==========================
// Các biến toàn cục
// ==========================
vector<int> par;          // cha trong "cây cầu" (bridge tree)
vector<int> dsu_2ecc;     // DSU quản lý 2-edge-connected components (2ECC)
vector<int> dsu_cc;       // DSU quản lý connected components (CC)
vector<int> dsu_cc_size;  // kích thước của mỗi CC
int bridges;              // số lượng bridges hiện tại trong đồ thị
int lca_iteration;        // biến dùng để đánh dấu vòng lặp tìm LCA trong merge_path
vector<int> last_visit;   // lưu lần cuối mỗi đỉnh được thăm trong merge_path


// ==========================
// Khởi tạo với n đỉnh ban đầu
// ==========================
void init(int n) {
    par.resize(n);
    dsu_2ecc.resize(n);
    dsu_cc.resize(n);
    dsu_cc_size.resize(n);
    lca_iteration = 0;
    last_visit.assign(n, 0);

    for (int i=0; i<n; ++i) {
        dsu_2ecc[i] = i;    // ban đầu, mỗi đỉnh là 1 2ECC riêng
        dsu_cc[i] = i;      // ban đầu, mỗi đỉnh là 1 CC riêng
        dsu_cc_size[i] = 1; // kích thước mỗi CC = 1
        par[i] = -1;        // chưa có cha trong "bridge tree"
    }
    bridges = 0;
}


// ==========================
// Tìm đại diện 2ECC của đỉnh v (DSU với path compression)
// ==========================
int find_2ecc(int v) {
    if (v == -1)
        return -1;
    return dsu_2ecc[v] == v ? v : dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}


// ==========================
// Tìm đại diện CC của đỉnh v
// ==========================
int find_cc(int v) {
    v = find_2ecc(v); // trước hết thu gọn theo 2ECC
    return dsu_cc[v] == v ? v : dsu_cc[v] = find_cc(dsu_cc[v]);
}


// ==========================
// Đặt v làm root mới trong cây cầu
// Ý nghĩa: thay đổi quan hệ cha/con để
// dễ dàng "nối" 2 cây cầu với nhau
// ==========================
void make_root(int v) {
    int root = v;
    int child = -1;
    while (v != -1) {
        int p = find_2ecc(par[v]); // cha của v trong bridge tree
        par[v] = child;            // đảo hướng cha-con
        dsu_cc[v] = root;          // tất cả node trên đường này sẽ thuộc cùng CC mới
        child = v;
        v = p;
    }
    dsu_cc_size[root] = dsu_cc_size[child]; // cập nhật kích thước CC
}


// ==========================
// Gom 2 đường đi từ a và b lại để tìm LCA
// (khi a và b thuộc cùng CC -> tạo ra chu trình)
// Từ đó gộp các đỉnh trên 2 đường này thành 1 2ECC
// và giảm số bridges (vì chu trình xuất hiện)
// ==========================
void merge_path (int a, int b) {
    ++lca_iteration;
    vector<int> path_a, path_b;
    int lca = -1;

    // Tìm Lowest Common Ancestor (LCA) của a và b trong bridge tree
    while (lca == -1) {
        if (a != -1) {
            a = find_2ecc(a);
            path_a.push_back(a);
            if (last_visit[a] == lca_iteration){
                lca = a; // tìm thấy LCA
                break;
            }
            last_visit[a] = lca_iteration;
            a = par[a];
        }
        if (b != -1) {
            b = find_2ecc(b);
            path_b.push_back(b);
            if (last_visit[b] == lca_iteration){
                lca = b; // tìm thấy LCA
                break;
            }
            last_visit[b] = lca_iteration;
            b = par[b];
        }
    }

    // Gom tất cả các node trên đường từ a -> LCA vào cùng 2ECC
    for (int v : path_a) {
        dsu_2ecc[v] = lca;
        if (v == lca) break;
        --bridges; // mỗi lần gộp lại thì 1 bridge biến mất
    }

    // Gom tất cả các node trên đường từ b -> LCA vào cùng 2ECC
    for (int v : path_b) {
        dsu_2ecc[v] = lca;
        if (v == lca) break;
        --bridges;
    }
}


// ==========================
// Thêm một cạnh (a, b) vào đồ thị
// Cập nhật số bridges hiện tại
// ==========================
void add_edge(int a, int b) {
    a = find_2ecc(a);
    b = find_2ecc(b);
    if (a == b)
        return; // cùng 2ECC rồi thì không ảnh hưởng gì

    int ca = find_cc(a);
    int cb = find_cc(b);

    if (ca != cb) {
        // Nếu a và b thuộc 2 CC khác nhau -> cạnh (a,b) là bridge mới
        ++bridges;

        // Đảm bảo nối CC nhỏ hơn vào CC lớn hơn (giống union by size)
        if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
            swap(a, b);
            swap(ca, cb);
        }

        // Đặt a làm root mới rồi nối nó vào b
        make_root(a);
        par[a] = dsu_cc[a] = b;
        dsu_cc_size[cb] += dsu_cc_size[a];
    } else {
        // Nếu a và b thuộc cùng CC -> thêm cạnh này tạo thành chu trình
        // Chu trình làm cho một số bridges biến mất
        merge_path(a, b);
    }
}
