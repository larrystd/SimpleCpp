// leetcode 37, 解数独

/*
编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
数独部分空格内已填入了数字，空白格用 '.' 表示

输入：board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
输出：[["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]

判断能不能填的逻辑
就依次填，硬暴力了。。。
*/
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<char> candidate = {'1', '2', '3', '4', '5', '6', '7', '8','9'};

        vector<vector<char>> result(board);

        dfs(board, result, 9, 0, 0, candidate);
    }

    void dfs(vector<vector<char>>&board, vector<vector<char>>&result,size_t n, int row, int column, vector<char>& candidate) {
        if (!isValidSudoku(result))
            return;
        if (row == n-1 && column == n) {
            board = result;
            return;
        }
            

        for (int i = 0; i < candidate.size(); i++) {
            if (result[row][column] == '.'){
                result[row][column] = candidate[i];
                if (column < n-1) {
                    dfs(board, result,n, row, column+1, candidate);
                }else{
                    dfs(board, result,n, row+1, 0, candidate);
                }
                result[row][column] = '.';
            }else {
                if (column < n-1) {
                    dfs(board, result,n, row, column+1, candidate);
                }else{
                    dfs(board, result,n, row+1, 0, candidate);
                }
            }
        }
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        // 检测横轴
        int n = board.size();
        for (int i = 0; i < n; i++) {
            if (!checkpart(board, i, i, 0, n-1))
                return false;
            if (!checkpart(board, 0, n-1, i, i))
                return false;
            
            if ((i+1) % 3 == 0) {
                for (int j = 0; j < 3; j++) {
                    if (!checkpart(board, i-2, i, j*3, j*3+2))
                        return false;
                }

            }
        }
        return true;
    }

    // []闭区间
    bool checkpart(vector<vector<char>>& board, int x_start, int x_end, int y_start, int y_end) {
        vector<int> nums(10);
        for (int i = x_start; i <= x_end; i++) {
            for (int j = y_start; j <= y_end; j++) {
                if (board[i][j] == '.')
                    continue;
                if (nums[board[i][j] - '0'] != 0)
                    return false;
                nums[board[i][j] - '0'] = 1;
            }
        }
        return true;
    }

private:
    bool line[9][9];
    bool column[9][9];
    bool block[3][3][9];
    bool valid;
    vector<pair<int, int>> spaces;

public:
    void dfs(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        for (int digit = 0; digit < 9 && !valid; ++digit) {
            if (!line[i][digit] && !column[j][digit] && !block[i / 3][j / 3][digit]) {
                line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
                board[i][j] = digit + '0' + 1;
                dfs(board, pos + 1);
                line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = false;
            }
        }
    }

    void solveSudoku_2(vector<vector<char>>& board) {
        memset(line, false, sizeof(line));
        memset(column, false, sizeof(column));
        memset(block, false, sizeof(block));
        valid = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
                else {
                    int digit = board[i][j] - '0' - 1;
                    line[i][digit] = column[j][digit] = block[i / 3][j / 3][digit] = true;
                }
            }
        }

        dfs(board, 0);
    }
};

int main() {
    vector<vector<char>> board = {{'5','3','.','.','7','.','.','.','.'}
                                    ,{'6','.','.','1','9','5','.','.','.'}
                                    ,{'.','9','8','.','.','.','.','6','.'}
                                    ,{'8','.','.','.','6','.','.','.','3'}
                                    ,{'4','.','.','8','.','3','.','.','1'}
                                    ,{'7','.','.','.','2','.','.','.','6'}
                                    ,{'.','6','.','.','.','.','2','8','.'}
                                    ,{'.','.','.','4','1','9','.','.','5'}
                                    ,{'.','.','.','.','8','.','.','7','9'}};
    Solution solu;
    solu.solveSudoku_2(board);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
} 

