/*
leetcode 306
累加数是一个字符串，组成它的数字可以形成累加序列。

一个有效的累加序列必须至少包含 3 个数。除了最开始的两个数以外，字符串中的其他数都等于它之前两个数相加的和。

给定一个只包含数字 '0'-'9' 的字符串，编写一个算法来判断给定输入是否是累加数。

说明: 累加序列里的数不会以 0 开头，所以不会出现 1, 2, 03 或者 1, 02, 3 的情况。

示例 1:

输入: "112358"
输出: true 
解释: 累加序列为: 1, 1, 2, 3, 5, 8 。1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        return dfs(num, 0, "-1", "-1", false);
    }

    bool dfs(string& num, int index, string prev, string pprev, bool issum) {
        if (index == num.size() && issum)
            return true;
        if (index== num.size() && !issum)
            return false;
        
        
        int flag = false;

        if (num[index] == '0') {
            if (prev == "-1" || pprev == "-1") {
                    flag = flag || dfs(num, index+1, "0", prev,false);
                }else if (str_sum(prev, pprev) == "0"){
                    flag = flag || dfs(num, index+1, "0", prev,true);
                }
        }
        else {

            for (int i = index; i < num.size(); i++) {
                string now = num.substr(index, i-index+1);
                //unsigned long long now_i = stoull(now);
                if (prev == "-1" || pprev == "-1") {
                    flag = flag || dfs(num, i+1, now, prev,false);
                }else if (str_sum(prev, pprev) == now){
                    flag = flag || dfs(num, i+1, now, prev,true);
                }else if(now > str_sum(prev, pprev)) {
                    break;  /// 没了
                }

            }

        }
        return flag;

        
    }

    string str_sum (string s1, string s2) {
            int i = s1.size()-1;
            int j = s2.size()-1;
            string s3("");
            int flag = 0;
            while (i>=0 && j >= 0) {
                int sum = flag + s1[i]-'0' + s2[j]-'0';
                s3.push_back(sum % 10+'0');
                flag = sum / 10;
                i--;
                j--;
            }
            while (i >= 0) {
                int sum = flag + s1[i] - '0';
                s3.push_back(sum % 10+'0');
                flag = sum / 10;
                i--;
            }
            while (j >= 0) {
                int sum = flag + s2[j] - '0';
                s3.push_back(sum % 10+'0');
                flag = sum / 10;
                j--;
            }

            if (flag != 0)
                s3.push_back(flag+'0');
            reverse(s3.begin(), s3.end());
            return s3;
        }


};

int main() {
    Solution solu;
    //string num("12012122436");
    //string num("2461016264268110179");

    cout << solu.str_sum("0","0")<<endl;
    string num("101");
    cout << solu.isAdditiveNumber(num) <<endl;
    return 0;
}