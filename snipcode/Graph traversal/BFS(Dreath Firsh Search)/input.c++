import java.util.*;

public class BFSInput {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // number of nodes
        int m = sc.nextInt(); // number of edges

        // initialize adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        // read edges
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adj.get(u).add(v);
            adj.get(v).add(u); // bỏ dòng này nếu đồ thị có hướng
        }

        int s = sc.nextInt(); // source vertex

        // BFS variables
        Queue<Integer> q = new LinkedList<>();
        boolean[] used = new boolean[n];
        int[] d = new int[n];
        int[] p = new int[n];

        Arrays.fill(p, -1);

        // BFS start
        q.add(s);
        used[s] = true;

        while (!q.isEmpty()) {
            int v = q.poll();
            for (int u : adj.get(v)) {
                if (!used[u]) {
                    used[u] = true;
                    q.add(u);
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
            }
        }

        // In thử kết quả
        System.out.println("Distance array: " + Arrays.toString(d));
        System.out.println("Parent array:   " + Arrays.toString(p));
    }
}
