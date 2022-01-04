// 有效的井数字

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int numX = 0;
        int numO = 0;
        for (auto& str : board) {
            for (char c : str) {
                if (c == 'X')
                    numX++;
                else if (c == 'O')
                    numO++;
            }
        }

        if (numX - numO > 1 || numX - numO < 0)
            return false;
        
        int success_num = 0;
        
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                if (success_num > 0)
                    return false;
                else
                    success_num++;
            }
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
                if (success_num > 0)
                    return false;
                else
                    success_num++;
            }
        }

        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
                if (success_num > 0)
                    return false;
                else
                    success_num++;
        }

        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            if (success_num > 0)
                return false;
            else
                success_num++;
        }

        return true;

    }
};

int main() {
    vector<string> board{"XXX","OOX","OOX"};
    Solution solu;
    cout << solu.validTicTacToe(board) <<endl;


    return 0;
}