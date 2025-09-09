// Bài toán

// Mô tả:
// Cho một mảng số nguyên A[0..n-1]. Hãy xây dựng Cartesian Tree từ mảng đó theo min-heap property và inorder traversal = A.
// Sau khi xây dựng, hãy in ra parent của mỗi node (chỉ số node cha, với root có parent = -1).

// Input:
// Dòng 1: số nguyên n (số lượng phần tử).
// Dòng 2: n số nguyên: A[0], A[1], ..., A[n-1].

// Output:
// Một dòng n số: parent[i] (chỉ số cha của node i, -1 nếu là root).

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    vector<int> parent(n, -1);
    stack<int> s;

    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!s.empty() && A[s.top()] >= A[i]) {
            last = s.top();
            s.pop();
        }

        if (!s.empty())
            parent[i] = s.top();

        if (last != -1)
            parent[last] = i;

        s.push(i);
    }

    for (int i = 0; i < n; i++) {
        cout << parent[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
