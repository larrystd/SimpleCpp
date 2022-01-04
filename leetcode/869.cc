//重新排序得到 2 的幂
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> visited;
    unordered_set<int> tables;
    bool reorderedPowerOf2(int n) {

        const int MAX = 1000000000;
        int i = 1;
        while (i < MAX) {   /// 所有2的次幂
            tables.insert(i);
            i = i*2;
        }

        string num_str("");
        while (n) {
            num_str.push_back(n % 10 + '0');
            n /= 10;
        }   // 转为字符串表示
        //cout << num_str<<endl;

        int len = num_str.size();
        visited.resize(len);
        string cur("");

        return trackback(num_str, cur);
    }


    bool trackback (string& num_str, string& cur) {
        if (cur.size() == num_str.size()) {
            int number = 0;
            int time = 1;

            /// 防止001这种情况, 求成1
            int len = cur.size();
            if (len > 1 && cur[len-1] == '0')
                return false;
            for (int i = 0; i < len; i++) {
                number += time*(cur[i] - '0');
                time *=10;
            }
            if (tables.count(number))
                return true;

            return false;
        }
        for (int i = 0; i < num_str.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                cur.push_back(num_str[i]);
                if (trackback(num_str, cur))    
                    return true;
                visited[i] = false;
                cur.pop_back();
            }
        }
        return false;
    }
};

int main() {
    Solution solu;
    cout << solu.reorderedPowerOf2(100) <<endl;

    return 0;
}