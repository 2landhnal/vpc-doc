#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// hàm nhân modulo
long long mul(long long a, long long b) {
    return (a % MOD) * (b % MOD) % MOD;
}

// hàm cộng modulo
long long add(long long a, long long b) {
    return (a + b) % MOD;
}

// Tính định thức ma trận bằng Gaussian elimination (mod MOD)
long long determinant(vector<vector<long long>> a, int n) {
    long long det = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (a[j][i] != 0) { pivot = j; break; }
        }
        if (a[pivot][i] == 0) return 0; // cột toàn 0
        if (pivot != i) {
            swap(a[pivot], a[i]);
            det = (MOD - det) % MOD; // đổi hàng => đổi dấu
        }
        det = mul(det, a[i][i]);
        long long inv = 1, base = a[i][i], exp = MOD - 2; // nghịch đảo Fermat
        while (exp) {
            if (exp & 1) inv = mul(inv, base);
            base = mul(base, base);
            exp >>= 1;
        }
        for (int j = i + 1; j < n; j++) {
            long long factor = mul(a[j][i], inv);
            for (int k = i; k < n; k++) {
                a[j][k] = (a[j][k] - mul(factor, a[i][k]) + MOD) % MOD;
            }
        }
    }
    return det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> L(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v; // đổi sang 0-index
        if (u == v) continue; // bỏ self-loop nếu có
        L[u][u]++;
        L[v][v]++;
        L[u][v]--;
        L[v][u]--;
    }

    // Xóa hàng 0 và cột 0
    vector<vector<long long>> M(n - 1, vector<long long>(n - 1));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            M[i - 1][j - 1] = (L[i][j] % MOD + MOD) % MOD;
        }
    }

    cout << determinant(M, n - 1) % MOD << "\n";
    return 0;
}
