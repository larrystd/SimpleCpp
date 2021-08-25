#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {

        int n = s.size();
        bool isEven = n / k % 2 == 0;

        bool flag = true;
        int x = 0;

        while ((x+1)*k <= n) {
            
            if (flag) {
                int i = x*k;
                int j = (x+1)*k-1;
                 while (i < j) {
                    swap(s[i], s[j]);
                    i++;
                    j--;
                }
                flag = false;
            }else{
                flag = true;
            }
            x++;  
        }

        if (isEven){
            int i = x*k;
            int j = n-1;
                while (i < j) {
                swap(s[i], s[j]);
                i++;
                j--;
            }
        }

        return s;
    }
};

int main() {
    Solution s;
    cout << s.reverseStr("abcd",3)<<endl;
    return 0;
}