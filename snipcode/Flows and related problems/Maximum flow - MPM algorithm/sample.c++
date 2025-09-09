struct MPM{
    // Struct mô tả một cạnh trong đồ thị luồng
    struct FlowEdge{
        int v, u;             // v: đỉnh xuất phát, u: đỉnh kết thúc
        long long cap, flow;  // cap: sức chứa, flow: luồng hiện tại
        FlowEdge(){}
        FlowEdge(int _v, int _u, long long _cap, long long _flow)
            : v(_v), u(_u), cap(_cap), flow(_flow){}
        FlowEdge(int _v, int _u, long long _cap)
            : v(_v), u(_u), cap(_cap), flow(0ll){}
    };

    const long long flow_inf = 1e18; // giá trị lớn dùng cho khởi tạo
    vector<FlowEdge> edges;           // danh sách các cạnh
    vector<char> alive;               // đánh dấu đỉnh còn "sống" trong layered network
    vector<long long> pin, pout;      // luồng tiềm năng đi vào/ra mỗi đỉnh
    vector<list<int>> in, out;        // danh sách các cạnh vào/ra "còn dư" theo layered network
    vector<vector<int>> adj;          // adjacency list của đồ thị
    vector<long long> ex;             // luồng dư (excess) trong preflow
    int n, m = 0;                     // n: số đỉnh, m: số cạnh (tăng 2 lần vì có residual)
    int s, t;                          // source và sink
    vector<int> level;                 // level graph (khoảng cách từ source)
    vector<int> q;                     // queue dùng cho BFS
    int qh, qt;                        // head và tail của queue

    // Khởi tạo kích thước dữ liệu
    void resize(int _n){
        n = _n;
        ex.resize(n);
        q.resize(n);
        pin.resize(n);
        pout.resize(n);
        adj.resize(n);
        level.resize(n);
        in.resize(n);
        out.resize(n);
    }

    MPM(){}
    MPM(int _n, int _s, int _t){resize(_n); s = _s; t = _t;}

    // Thêm một cạnh
    void add_edge(int v, int u, long long cap){
        edges.push_back(FlowEdge(v, u, cap)); // cạnh chính
        edges.push_back(FlowEdge(u, v, 0));   // cạnh residual
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    // BFS để tạo layered network
    bool bfs(){
        while(qh < qt){
            int v = q[qh++];
            for(int id : adj[v]){
                if(edges[id].cap - edges[id].flow < 1) continue; // cạnh đầy, bỏ qua
                if(level[edges[id].u] != -1) continue;          // đã thăm
                level[edges[id].u] = level[v] + 1;
                q[qt++] = edges[id].u;
            }
        }
        return level[t] != -1; // t có thể tới từ s không?
    }

    // Tính "potential flow" của một đỉnh v: min(pin, pout)
    long long pot(int v){
        return min(pin[v], pout[v]);
    }

    // Xóa đỉnh v khỏi layered network
    void remove_node(int v){
        for(int i : in[v]){
            int u = edges[i].v;
            auto it = find(out[u].begin(), out[u].end(), i);
            out[u].erase(it);            // xóa cạnh từ out[u]
            pout[u] -= edges[i].cap - edges[i].flow; // cập nhật residual capacity
        }
        for(int i : out[v]){
            int u = edges[i].u;
            auto it = find(in[u].begin(), in[u].end(), i);
            in[u].erase(it);
            pin[u] -= edges[i].cap - edges[i].flow;
        }
    }

    // Push luồng f từ from tới to theo hướng forward/backward
    void push(int from, int to, long long f, bool forw){
        qh = qt = 0;
        ex.assign(n, 0);
        ex[from] = f;
        q[qt++] = from;

        while(qh < qt){
            int v = q[qh++];
            if(v == to) break; // đã tới sink/source

            long long must = ex[v];
            auto it = forw ? out[v].begin() : in[v].begin();
            while(true){
                int u = forw ? edges[*it].u : edges[*it].v;
                long long pushed = min(must, edges[*it].cap - edges[*it].flow);
                if(pushed == 0) break;

                if(forw){
                    pout[v] -= pushed;
                    pin[u] -= pushed;
                } else {
                    pin[v] -= pushed;
                    pout[u] -= pushed;
                }

                if(ex[u] == 0) q[qt++] = u; // active vertex mới
                ex[u] += pushed;

                edges[*it].flow += pushed;
                edges[(*it)^1].flow -= pushed; // cập nhật residual

                must -= pushed;

                if(edges[*it].cap - edges[*it].flow == 0){
                    auto jt = it; ++jt;
                    if(forw){
                        in[u].erase(find(in[u].begin(), in[u].end(), *it));
                        out[v].erase(it);
                    } else {
                        out[u].erase(find(out[u].begin(), out[u].end(), *it));
                        in[v].erase(it);
                    }
                    it = jt;
                } else break;

                if(!must) break;
            }
        }
    }

    // Thuật toán chính: tính max-flow
    long long flow(){
        long long ans = 0;
        while(true){
            // Reset dữ liệu cho vòng lặp
            pin.assign(n, 0);
            pout.assign(n, 0);
            level.assign(n, -1);
            alive.assign(n, true);
            level[s] = 0;
            qh = 0; qt = 1;
            q[0] = s;

            if(!bfs()) break; // không còn đường tăng nữa

            // Tạo layered network
            for(int i = 0; i < n; i++){
                out[i].clear();
                in[i].clear();
            }
            for(int i = 0; i < m; i++){
                if(edges[i].cap - edges[i].flow == 0) continue;
                int v = edges[i].v, u = edges[i].u;
                if(level[v] + 1 == level[u] && (level[u] < level[t] || u == t)){
                    in[u].push_back(i);
                    out[v].push_back(i);
                    pin[u] += edges[i].cap - edges[i].flow;
                    pout[v] += edges[i].cap - edges[i].flow;
                }
            }
            pin[s] = pout[t] = flow_inf;

            // Push luồng tối đa từ các đỉnh "alive" cho đến khi không còn
            while(true){
                int v = -1;
                for(int i = 0; i < n; i++){
                    if(!alive[i]) continue;
                    if(v == -1 || pot(i) < pot(v))
                        v = i;
                }
                if(v == -1) break; // hết đỉnh khả dụng

                if(pot(v) == 0){
                    alive[v] = false;
                    remove_node(v); // loại bỏ đỉnh không còn khả năng push
                    continue;
                }

                long long f = pot(v);
                ans += f;
                push(v, s, f, false); // push về source
                push(v, t, f, true);  // push về sink
                alive[v] = false;
                remove_node(v);
            }
        }
        return ans; // max-flow
    }
};
