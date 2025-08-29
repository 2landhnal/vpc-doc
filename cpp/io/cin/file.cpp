#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // đọc từ input.txt và ghi ra output.txt
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int row, col;
    scanf("%d %d", &row, &col);

    vector<vector<int>> mat(row, vector<int>(col));

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> mat[i][j];
        }
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
