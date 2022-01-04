#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<int>> dp_l(rows+1, vector<int>(cols+1, 0x3f3f3f3f));
        vector<vector<int>> dp_r(dp_l);
        vector<vector<int>> result(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] == 0)
                    dp_l[i+1][j+1] = 0;
                else {
                    dp_l[i+1][j+1] = min(dp_l[i][j+1], dp_l[i+1][j])+1;
                }
            }
        }

        for (int i = rows-1; i >=0; i--) {
            for (int j = cols-1; j >=0; j--) {
                if (mat[i][j] == 0)
                    dp_r[i][j] = 0;
                else {
                    int min_l = 0x3f3f3f3f;
                    min_l = min(min_l, dp_l[i][j+1]);
                    min_l = min(min_l, dp_l[i+1][j]);
                    if (i != rows-1) {
                        min_l = min(min_l, dp_l[i+2][j+1]);
                    }
                    if (j != cols-1)
                        min_l = min(min_l, dp_l[i+1][j+2]);
                    dp_r[i][j] = min(dp_r[i][j+1], min(min_l,dp_r[i+1][j]))+1;
                }
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] = dp_r[i][j];
            }
        }
        return result;

    }
};

int main() {
    vector<vector<int>> mat ={{0,0,1,0,1,1,1,0,1,1},{1,1,1,1,0,1,1,1,1,1}, {1,1,1,1,1,0,0,0,1,1}, {1,0,1,0,1,1,1,0,1,1}, {0,0,1,1,1,0,1,1,1,1}, {1,0,1,1,1,1,1,1,1,1}, {1,1,1,1,0,1,0,1,0,1}, {0,1,0,0,0,1,0,0,1,1}, {1,1,1,0,1,1,0,1,0,1}, {1,0,1,1,1,0,1,1,1,0}};

    for (auto& res : mat) {
        for (int e : res) {
            cout << e << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    Solution solu;
    auto result = solu.updateMatrix(mat);

    for (auto& res : result) {
        for (int e : res) {
            cout << e << " ";
        }
        cout << "\n";
    }
    return 0;
}