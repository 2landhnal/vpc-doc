#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int n, m, K;

using Matrix = vector<vector<int>>;

// nhân ma trận trong "min-plus algebra"
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A[i][k] == INF) continue; 
            for (int j = 0; j < n; j++) {
                if (B[k][j] == INF) continue;
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    return C;
}

// lũy thừa ma trận bằng binary exponentiation
Matrix power(Matrix base, int exp) {
    int n = base.size();
    // ma trận đơn vị theo ngữ cảnh min-plus
    Matrix res(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) res[i][i] = 0;
    
    while (exp > 0) {
        if (exp & 1) res = multiply(res, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    cin >> n >> m >> K;
    Matrix A(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        A[u][v] = min(A[u][v], w); // chọn cạnh nhỏ nhất nếu có nhiều
    }

    Matrix Ak = power(A, K);

    int s, t;
    cin >> s >> t;
    --s; --t;
    if (Ak[s][t] == INF) cout << "No path of length " << K << "\n";
    else cout << "Shortest path of length " << K << " = " << Ak[s][t] << "\n";
}
