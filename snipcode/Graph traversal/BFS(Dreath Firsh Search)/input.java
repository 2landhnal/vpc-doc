import java.util.*;

public class AdjacencyListInput {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // số đỉnh
        int m = sc.nextInt(); // số cạnh

        // tạo adjacency list bằng LinkedList
        LinkedList<Integer>[] adj = new LinkedList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new LinkedList<>();
        }

        // đọc m cạnh
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();

            adj[u].add(v);     // thêm cạnh u → v (luôn giữ)
            adj[v].add(u);     // chỉ thêm nếu đồ thị VÔ HƯỚNG
        }

        // in thử adjacency list
        for (int i = 0; i < n; i++) {
            System.out.print(i + ": ");
            for (int v : adj[i]) {
                System.out.print(v + " ");
            }
            System.out.println();
        }
    }
}
