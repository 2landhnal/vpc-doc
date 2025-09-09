import java.util.*;

public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        n = sc.nextInt();
        m = sc.nextInt();

        adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>()); // khởi tạo list rỗng cho từng đỉnh
        }

        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adj.get(u).add(v);
            adj.get(v).add(u); // bỏ dòng này nếu là đồ thị có hướng
        }

        visited = new boolean[n];

        // chạy DFS từ đỉnh 0
        dfs(0);
    }