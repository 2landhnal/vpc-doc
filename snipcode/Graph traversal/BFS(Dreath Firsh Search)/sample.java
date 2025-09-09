ArrayList<ArrayList<Integer>> adj = new ArrayList<>(); // danh sách kề

int n; // số nodes
int s; // đỉnh bắt đầu


LinkedList<Integer> q = new LinkedList<Integer>();
boolean used[] = new boolean[n];
int d[] = new int[n];
int p[] = new int[n];

q.push(s);
used[s] = true;
p[s] = -1;
while (!q.isEmpty()) {
    int v = q.pop();
    for (int u : adj.get(v)) {
        if (!used[u]) {
            used[u] = true;
            q.push(u);
            d[u] = d[v] + 1;
            p[u] = v;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// If we have to restore and display the shortest path from the source to some vertex  
// u , it can be done in the following manner:

if (!used[u]) {
    System.out.println("No path!");
} else {
    ArrayList<Integer> path = new ArrayList<Integer>();
    for (int v = u; v != -1; v = p[v])
        path.add(v);
    Collections.reverse(path);
    for(int v : path)
        System.out.println(v);
}