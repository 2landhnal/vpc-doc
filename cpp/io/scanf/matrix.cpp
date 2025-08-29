#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int row, col;
    scanf("%d %d", &row, &col);

    vector<vector<int>> mat(row, vector<int>(col));

    // nhập ma trận
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }

    // in ma trận
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}
