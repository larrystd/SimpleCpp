// 59 螺旋矩阵

/*
给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n,0));

        if (n == 1)
            return vector<vector<int>>{{1}};
        if (n == 2)
            return vector<vector<int>>{{1,2}, {4,3}};

        int start = 0;
        int count = 0;
        int i;

        while (matrix[start][start] == 0) {
            for (i = start; i < n-start; i++) {
                ++count;
                matrix[start][i] = count;
            }
            // n-start-1个
            bool isbottom = false;
            for (i = start + 1; i < n-start; i++) {
                ++count;
                matrix[i][n-1-start] = count;
                isbottom = true;
            }
            if (isbottom) {
                for (i = n-start-2; i >= start; i--) {
                    ++count;
                    matrix[n-1-start][i] = count;
                }
                for (i = n-start-2; i > start; i--) {
                    ++count;
                    matrix[i][start] = count;
                }
            }

            start++;
        }
        return matrix;

    }
};


int main() {
    Solution solu;
    vector<vector<int>> matrix = solu.generateMatrix(6);
    for (auto& m : matrix) {
        for (auto& e : m) {
            cout << e << " ";
        }
        cout << "\n";
    }
    return 0;
}