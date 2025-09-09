// Cấu trúc biểu diễn 1 cạnh của đồ thị
struct Edge {
    int u, v, weight;   // cạnh nối đỉnh u và v, có trọng số = weight
    
    // So sánh 2 cạnh theo trọng số (dùng để sort)
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;                  // số đỉnh trong đồ thị
vector<Edge> edges;     // danh sách các cạnh (u, v, w)

int cost = 0;           // tổng chi phí (trọng số) của cây khung nhỏ nhất
vector<int> tree_id(n); // mảng đánh dấu "thành phần liên thông" hiện tại của mỗi đỉnh
vector<Edge> result;    // danh sách các cạnh thuộc cây khung nhỏ nhất

// Ban đầu: mỗi đỉnh ở trong một thành phần riêng biệt
for (int i = 0; i < n; i++)
    tree_id[i] = i;

// Bước 1: Sắp xếp các cạnh theo trọng số tăng dần
sort(edges.begin(), edges.end());

// Bước 2: Duyệt qua từng cạnh
for (Edge e : edges) {
    // Nếu 2 đỉnh u, v thuộc về 2 thành phần khác nhau (chưa kết nối)
    if (tree_id[e.u] != tree_id[e.v]) {
        // -> Ta chọn cạnh này vào MST
        cost += e.weight;
        result.push_back(e);

        // Gộp 2 thành phần lại thành 1
        int old_id = tree_id[e.u];
        int new_id = tree_id[e.v];
        for (int i = 0; i < n; i++) {
            if (tree_id[i] == old_id)
                tree_id[i] = new_id;  // đổi nhãn tất cả các đỉnh thuộc old_id -> new_id
        }
    }
}
