// C++ program to demonstrate how to take input in an array
#include <iostream>
#include <vector>
using namespace std;

// driver code
int main()
{
    int row, col;
    cin >> row >> col;
    vector<vector<int>> mat(row, vector<int>(col));
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j) cin >> mat[i][j];
    }
    for(int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j) cout << mat[i][j] << " ";
        cout << "\n";
    }
    return 0;
}