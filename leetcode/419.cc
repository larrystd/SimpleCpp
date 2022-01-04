#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> visited_;
    int countBattleships(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        visited_.assign(m, vector<int>(n));

        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'X' && visited_[i][j] == 0) {
                    result++;
                    for (int k = j; k < n; k++) {
                        if (board[i][k] == '.')
                            break;
                        visited_[i][k] = 1;
                    }

                
                    for (int l = i; l < m; l++) {
                        if (board[l][j] == 'O')
                            break;
                        visited_[l][j] = 1;
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    vector<vector<char>> board = {{'X','.','.','X'},{'.','.','.','X'},{'.','.','.','X'}};

    Solution solu;
    cout << solu.countBattleships(board) <<"\n";

    return 0;
}