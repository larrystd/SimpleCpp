/*
比较版本号

版本号由一个或多个修订号组成，各修订号由一个 '.' 连接。每个修订号由 多位数字 组成，可能包含 前导零 。
每个版本号至少包含一个字符。修订号从左到右编号，下标从 0 开始，最左边的修订号下标为 0 ，下一个修订号下标为 1 ，以此类推。例如，2.5.33 和 0.1 都是有效的版本号。

比较版本号时，请按从左到右的顺序依次比较它们的修订号。比较修订号时，只需比较 忽略任何前导零后的整数值 。
也就是说，修订号 1 和修订号 001 相等 。如果版本号没有指定某个下标处的修订号，则该修订号视为 0 

输入：version1 = "1.01", version2 = "1.001"
输出：0
解释：忽略前导零，"01" 和 "001" 都表示相同的整数 "1"

按照.来切分字符串，比较每个小块。

c++ find函数，size_t find (const string& str, size_t pos = 0) const; 从pos开始找，返回第一个
如果没有找到，那么会返回一个特别的标记npos。

字符串比较
compare()

s1.compare(s2)
*/

#include <iostream>
#include <string>

using namespace std;


class Solution {
public:

    int comparePartStr(string str1, string str2) {
        int i = 0;
        while (i < str1.size() && str1[i] == '0'){
            i++;
        }
        int j = 0;
        while (j < str2.size() && str2[j] == '0') {
            j++;
        }
        if (i == str1.size() && j == str2.size()){
            return 0;
        }
        return str1.substr(i).compare( str2.substr(j));
    }
    int compareVersion(string version1, string version2) {
        size_t part_left_1 = 0, part_left_2 =0;
        size_t part_right_1 = version1.find('.', part_left_1);
        size_t part_right_2 = version2.find('.', part_left_2);
        while (part_right_1 != version1.npos && part_right_2 != version2.npos) {
            int tmp = comparePartStr(version1.substr(part_left_1, part_right_1-part_left_1), version2.substr(part_left_2, part_right_2-part_left_2));
            if (tmp == 0){
                part_left_1 = part_right_1+1;
                part_left_2 = part_right_2 + 1;
                part_right_1 = version1.find('.', part_left_1);
                part_right_2 = version2.find('.', part_left_2);
            } else {
                return tmp;
            }
        }

        while (part_right_1 != version1.npos) {
            int tmp = comparePartStr(version1.substr(part_left_1, part_right_1-part_left_1), string("0"));
            if (tmp == 0){
                part_left_1 = part_right_1+1;
                part_right_1 = version1.find('.', part_left_1);
            } else {
                return tmp;
            }
        }

        while (part_right_2 != version2.npos) {
            int tmp = comparePartStr( string("0"), version2.substr(part_left_2, part_right_2-part_left_2));
            if (tmp == 0){
                part_left_2 = part_right_2+1;
                part_right_2 = version2.find('.', part_left_2);
            } else {
                return tmp;
            }
        }

        return 0;
    }
};

int main() {
    Solution s;
    cout << s.compareVersion("1.0", "1.0.1") <<endl;
    return 0;
}