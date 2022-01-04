#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> nums_s;
        for (int i = 0 ; i< nums.size(); i++) {
            string s = "";
            int n = nums[i];
            if (n==0) {
                s.push_back('0');
                nums_s.push_back(s);
                continue;
            }
            while (n) {
                s.push_back(n%10 + '0');
                n /= 10;
            }
            reverse(s.begin(), s.end());
            nums_s.push_back(s);
        }

        sort(nums_s.begin(), nums_s.end(), [](const auto& a, const auto& b) {

            // 比较ab, ba哪个大, 如果ab大返回true
            if (a == b)
                return true;
            
            string ab = a + b;
            string ba = b + a;
            int n = ab.size();

            for (int i = 0; i < n; i++) {
                if (ab[i] != ba[i])
                    return ab[i] > ba[i];
            }
            return true;
        });

        string res = "";

        //
        int i;
        for (i = 0; i < nums_s.size()-1; i++) {
            if (nums_s[i] != "0")
                break;
        }
        for (int j = i; j < nums_s.size(); j++) {
            res.append(nums_s[j]);
        }
        return res;
    }
};

int main() {

    Solution s;
    vector<int> vect = {0,0,0,0};
    cout << s.largestNumber(vect)<<endl;
    return 0;
}