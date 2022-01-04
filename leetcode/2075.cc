// leetcode 2075 解码斜向换位密码

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        //if (rows == 1)
        //    return encodedText;
        int size = encodedText.size();
        int len = size/rows;
        string result("");
        int cur_col = 0;
        int cur_index = 0;
        int top_col = 0; // 第一行当前列
        bool isstop = false;
        while (!isstop) {
            cur_index = top_col;
            cur_col = top_col;
            for (int i = 0; i < rows; i++) {
                if (cur_col >= len) {
                    isstop = true;
                    break;
                }
                result.push_back(encodedText[cur_index]);
                cur_index += (len + 1);
                cur_col++;
            }
            top_col ++;
        }

        return result;
    }
};

int main() {
    string encoded_text = "iveo    eed   l te   olc";
    int rows = 4;
    Solution solu;
    cout << solu.decodeCiphertext(encoded_text, rows) <<endl;

    return 0;
}