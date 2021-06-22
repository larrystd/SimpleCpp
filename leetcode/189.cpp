/*
给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。给你 m x n 网格面板 board 的当前状态，返回下一个状态。

*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        vector<vector<int>> board_mark = board;
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                int sum = 0;
                for (int dx = -1; dx <=1; dx++) {
                    int pos_x = x + dx;
                    if (pos_x < 0 || pos_x >= rows)
                        continue;
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0)
                            continue;
                        int pos_y = y+dy;
                        if (pos_y < 0 || pos_y >= cols)
                            continue;
                        if (board[pos_x][pos_y] == 1) {
                            sum++;
                        }
                    }
                }
                if (board[x][y] == 1 && (sum <2 || sum > 3))
                    board_mark[x][y] = 0;
                if (board[x][y] == 0 && sum == 3)
                    board_mark[x][y] = 1;
                
            }
        }
        board = board_mark;
    }
};

int main() {
    vector<vector<int>> board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};

    Solution s;
    s.gameOfLife(board);

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j] <<" ";
        }
        cout<<endl;
    }
    return 0;
}