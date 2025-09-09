Ok, hiểu rồi 👍. Mình sẽ list cho bạn các **pattern thường gặp trong giải thuật đồ thị** (ICPC/LeetCode kiểu), kèm hướng xử lý và **độ phức tạp ước lượng**.

---

## 🔹 Các pattern phổ biến trong giải thuật đồ thị

### 1. **Kiểm tra tính liên thông / có đường đi hay không**

* **Mô tả**: Xem hai đỉnh có cùng thành phần liên thông không.
* **Giải pháp**:

  * **Union-Find (Disjoint Set Union – DSU)**:

    * Union + Find: `O(α(n))` (gần như hằng số).
    * Xây DSU cho `m` cạnh: `O(m α(n))`.
  * **DFS/BFS**: `O(n + m)`.

---

### 2. **Đường đi ngắn nhất (Shortest Path)**

* **Mô tả**: Tìm đường đi ngắn nhất từ 1 đỉnh đến các đỉnh khác.
* **Giải pháp**:

  * **Dijkstra (không âm)**:

    * `O((n + m) log n)` (với heap).
  * **Bellman-Ford (có cạnh âm)**:

    * `O(n*m)`.
  * **Floyd-Warshall (all-pairs shortest path)**:

    * `O(n^3)`.

---

### 3. **Chu trình (Cycle Detection)**

* **Trong đồ thị vô hướng**:

  * DFS + DSU: `O(n + m)`.
* **Trong đồ thị có hướng**:

  * DFS + stack (kiểm tra back-edge): `O(n + m)`.

---

### 4. **Topological Sort (sắp xếp topo)**

* **Mô tả**: Sắp xếp các đỉnh trong đồ thị có hướng không chu trình (DAG).
* **Giải pháp**:

  * DFS + stack: `O(n + m)`.
  * BFS (Kahn’s algorithm): `O(n + m)`.

---

### 5. **Cầu và Khớp (Bridges & Articulation Points)**

* **Mô tả**: Xác định cạnh/đỉnh mà khi bỏ đi sẽ tách đồ thị.
* **Giải pháp**:

  * DFS + Low-link (Tarjan): `O(n + m)`.

---

### 6. **Thành phần liên thông mạnh (SCC)**

* **Mô tả**: Chia đồ thị có hướng thành các thành phần liên thông mạnh.
* **Giải pháp**:

  * **Kosaraju**: 2 lần DFS `O(n + m)`.
  * **Tarjan**: 1 lần DFS `O(n + m)`.

---

### 7. **Cây khung nhỏ nhất (MST)**

* **Mô tả**: Tìm cây khung nhỏ nhất.
* **Giải pháp**:

  * **Kruskal + DSU**: `O(m log n)`.
  * **Prim + heap**: `O(m log n)`.

---

### 8. **Chu trình Euler & Đường đi Hamilton**

* **Eulerian Path/Circuit**: Kiểm tra bậc của đỉnh + DFS `O(n + m)`.
* **Hamiltonian Path**: NP-hard → dùng **backtracking/bitmask DP** `O(n * 2^n)`.

---

### 9. **Bài toán luồng (Max Flow / Min Cut)**

* **Ford-Fulkerson**: `O(max_flow * m)`.
* **Edmonds-Karp**: `O(n * m^2)`.
* **Dinic**: `O(min(n^(2/3), √m) * m)`.
* **Push-Relabel**: \~`O(n^3)`.

---

### 10. **Matching (Ghép cặp)**

* **Bipartite Matching (Hungarian / Kuhn / Hopcroft-Karp)**:

  * Hopcroft-Karp: `O(√n * m)`.
* **General Matching (Blossom algorithm)**: `O(n^3)`.

---

### 11. **Chu trình ngắn nhất chứa mọi đỉnh (TSP)**

* **Bitmask DP**: `O(n^2 * 2^n)`.
* **Heuristic / Approximation** nếu n lớn.

---

### 12. **Đường đi với ràng buộc (k cạnh, k trọng số, …)**

* **DP trên đồ thị**: `O(n * k)` hoặc `O(n * k log n)` tùy ràng buộc.
* **K-shortest paths (Yen’s / Eppstein)**: `O(k n log n)`.

---

### 13. **Cây bao trùm ngắn nhất nhiều nguồn (Steiner Tree)**

* NP-hard, dùng **DP bitmask trên terminal**: `O(3^k * n + 2^k * n log n)`.

---

### 14. **2-SAT (Ràng buộc logic trên đồ thị)**

* **Xây đồ thị hàm kéo theo + SCC**: `O(n + m)`.

---

### 15. **Chu trình âm (Negative Cycle)**

* Bellman-Ford hoặc **Floyd-Warshall** để phát hiện.

---

👉 Tóm lại, **pattern chính** thường gặp trong thi ICPC/LeetCode về đồ thị:

* **Connectivity** (Union-Find / BFS/DFS) → `O(n+m)`
* **Shortest Path** (Dijkstra, Bellman-Ford, Floyd) → `O(m log n)`, `O(n*m)`, `O(n^3)`
* **MST** (Kruskal/Prim) → `O(m log n)`
* **SCC / Topo sort** → `O(n+m)`
* **Max Flow / Min Cut** → `O(n^3)` hoặc tốt hơn với Dinic
* **Matching** → `O(√n * m)` hoặc `O(n^3)`
* **TSP & các bài toán NP-hard** → `O(2^n * poly(n))`

---