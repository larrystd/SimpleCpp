/*
检查句子中的数字是否递增

连续数字
数字都是正整数
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:


    bool areNumbersAscending(string s) {
        int n = s.size();
        int i = 0;
        int cur;
        int prev = -1;
        int left = 0;
        int right = 0;
        while (left < n) {
            right = left;
            while(right < n && s[right] >= '0' && s[right] <= '9') {
                right++;
            }
            // [i,j)
            if (right != left) {
                cur = 0;
                int time = 1;
                for (int i = right-1; i >= left; i--) {
                    cur += time*(s[i]-'0');
                    time *= 10;
                }
                if (cur <= prev) {
                    return false;
                }
                prev = cur;
            } // 有数
            
            left = right+1;
        }

        return true;
    }
};

int main() {
    Solution solu;
    string str("4 5 11 26");
    cout << solu.areNumbersAscending(str)<<endl;

    return 0;
}