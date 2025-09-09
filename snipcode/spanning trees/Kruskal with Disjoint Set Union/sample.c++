// ===============================
// Giải bài toán Minimum Spanning Tree (MST)
// bằng thuật toán Kruskal với DSU (Disjoint Set Union / Union-Find)
// ===============================

vector<int> parent, rank; // DSU: mảng cha và mảng "rank" (chiều cao xấp xỉ của cây)

// Khởi tạo một tập hợp riêng lẻ cho đỉnh v
void make_set(int v) {
    parent[v] = v; // mỗi đỉnh là cha của chính nó (tập hợp chỉ có 1 phần tử)
    rank[v] = 0;   // ban đầu cây chỉ có 1 node nên rank = 0
}

// Tìm gốc đại diện (leader) của tập hợp chứa v
// kèm tối ưu hóa path compression (nén đường đi)
int find_set(int v) {
    if (v == parent[v])
        return v; 
    return parent[v] = find_set(parent[v]); 
}

// Hợp nhất hai tập hợp chứa a và b
// dùng union by rank để giữ cây cân bằng
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        // Đặt cây có rank lớn hơn làm cha để giảm chiều cao
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++; // nếu bằng nhau thì tăng rank
    }
}

// Cấu trúc lưu một cạnh của đồ thị
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight; // so sánh để sort theo trọng số tăng dần
    }
};

int n;                // số đỉnh của đồ thị
vector<Edge> edges;   // danh sách tất cả các cạnh (u, v, weight)

int cost = 0;         // tổng trọng số của cây khung nhỏ nhất
vector<Edge> result;  // danh sách các cạnh thuộc MST

// Khởi tạo DSU
parent.resize(n);
rank.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);

// B1: Sắp xếp tất cả các cạnh theo trọng số tăng dần
sort(edges.begin(), edges.end());

// B2: Duyệt các cạnh, nếu u và v thuộc 2 thành phần khác nhau thì chọn cạnh này
for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;        // cộng trọng số vào chi phí MST
        result.push_back(e);     // lưu cạnh này vào MST
        union_sets(e.u, e.v);    // gộp hai thành phần lại
    }
}

// Sau khi duyệt xong: 
// - "cost" là tổng trọng số nhỏ nhất
// - "result" chứa n-1 cạnh của cây khung nhỏ nhất
