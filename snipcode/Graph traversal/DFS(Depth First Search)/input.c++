import java.util.*;

public class DFSInput {
    static List<List<Integer>> adj = new ArrayList<>();
    static boolean[] visited;

    static void dfs(int v) {
        visited[v] = true;
        for (int u : adj.get(v)) {
            if (!visited[u]) {
                dfs(u);
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // number of vertices
        int m = sc.nextInt(); // number of edges

        // initialize adjacency list
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        // read edges
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adj.get(u).add(v);
            adj.get(v).add(u); // bỏ nếu là đồ thị có hướng
        }

        int s = sc.nextInt(); // starting vertex

        visited = new boolean[n];

        // chạy DFS từ s
        dfs(s);

        // In thử các đỉnh đã thăm
        System.out.print("Visited nodes: ");
        for (int i = 0; i < n; i++) {
            if (visited[i]) System.out.print(i + " ");
        }
    }
}
