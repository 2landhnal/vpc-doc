// Mã cơ bản (không xử lý cạnh âm)
// d[i][j] = khoảng cách ngắn nhất hiện tại từ i -> j
// p[i][j] = đỉnh trung gian trên đường đi i -> j (ban đầu -1)

for (int k = 0; k < n; ++k) {                 // thử dùng đỉnh k làm trung gian
    for (int i = 0; i < n; ++i) {             // duyệt mọi cặp (i, j)
        for (int j = 0; j < n; ++j) {
            if (d[i][k] + d[k][j] < d[i][j]) {
                d[i][j] = d[i][k] + d[k][j];  // cập nhật khoảng cách tốt hơn
                p[i][j] = k;                  // lưu lại: đường i->j đi qua k
            }
        }
    }
}

//=========================================================================================
// d[i][j] = khoảng cách ngắn nhất hiện tại từ i -> j
// p[i][j] = đỉnh trung gian trên đường đi i -> j (ban đầu -1)

for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // chỉ xét khi i->k và k->j tồn tại (≠ INF)
            if (d[i][k] < INF && d[k][j] < INF) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];  // cập nhật khoảng cách
                    p[i][j] = k;                  // lưu trung gian k
                }
            }
        }
    }
}

//=========================================================================================
// Truy vết đường đi
vector<int> path; 

// Truy vết đường đi ngắn nhất từ đỉnh i đến đỉnh j
void get_path(int i, int j) {
    // Nếu không có đỉnh trung gian giữa i và j
    if (p[i][j] == -1) { 
        path.push_back(i);      // thêm đỉnh i
        if (i != j) path.push_back(j); // nếu i != j thì thêm luôn đỉnh j
    } else {
        int k = p[i][j];  // k là đỉnh trung gian trên đường đi ngắn nhất từ i -> j
        get_path(i, k);   // truy vết đường đi i -> k
        path.pop_back();  // xóa k đi để tránh bị lặp khi nối i->k và k->j
        get_path(k, j);   // truy vết đường đi k -> j
    }
}



