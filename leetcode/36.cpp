// leetcode 36.cpp

/*
请你判断一个 9x9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
数独部分空格内已填入了数字，空白格用 '.' 表示。

注意：

一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。

输入：board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
输出：true

/// 一共需要判断9+9+9 = 27次
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
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
    cout << solu.isValidSudoku(board) << endl;

    return 0;
}


