// Cấu trúc lưu trữ một cạnh (edge) của đồ thị
// a: đỉnh xuất phát, b: đỉnh đích, cost: trọng số cạnh
struct Edge {
    int a, b, cost;
};

// n: số đỉnh, m: số cạnh, v: đỉnh nguồn
int n, m, v;

// Danh sách các cạnh của đồ thị
vector<Edge> edges;

// Một hằng số INF dùng để biểu diễn "vô cực" (chưa biết đường đi nào)
const int INF = 1000000000;

void solve()
{
    vector<int> d(n, INF); 
    // d[u] = khoảng cách ngắn nhất tạm thời từ đỉnh xuất phát v đến u
    // ban đầu: tất cả vô cùng (INF)

    d[v] = 0; 
    // khoảng cách từ v đến v = 0

    for (;;) { 
        // vòng lặp vô hạn, sẽ break khi không có cập nhật mới
        bool any = false; // đánh dấu xem có relax cạnh nào không

        for (Edge e : edges) // duyệt toàn bộ các cạnh (a -> b, cost)
            if (d[e.a] < INF) // chỉ xét những cạnh từ đỉnh đã có đường đi
                if (d[e.b] > d[e.a] + e.cost) { 
                    // nếu đi qua e.a giúp rút ngắn khoảng cách tới e.b
                    d[e.b] = d[e.a] + e.cost; // cập nhật khoảng cách
                    any = true; // có relax → còn thay đổi
                }

        if (!any) // nếu duyệt hết các cạnh mà không có relax nào
            break; // tức là đã hội tụ, không thể rút ngắn thêm
    }

    // sau vòng lặp: d[u] chứa khoảng cách ngắn nhất từ v tới u
    // có thể in ra d để kiểm tra kết quả
    // display d, for example, on the screen
}
