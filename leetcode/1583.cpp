/*
给你一份 n 位朋友的亲近程度列表，其中 n 总是 偶数 。

对每位朋友 i，preferences[i] 包含一份 按亲近程度从高到低排列 的朋友列表。换句话说，排在列表前面的朋友与 i 的亲近程度比排在列表后面的朋友更高。每个列表中的朋友均以 0 到 n-1 之间的整数表示。

所有的朋友被分成几对，配对情况以列表 pairs 给出，其中 pairs[i] = [xi, yi] 表示 xi 与 yi 配对，且 yi 与 xi 配对。

但是，这样的配对情况可能会是其中部分朋友感到不开心。在 x 与 y 配对且 u 与 v 配对的情况下，如果同时满足下述两个条件，x 就会不开心：

x 与 u 的亲近程度胜过 x 与 y，且
u 与 x 的亲近程度胜过 u 与 v
返回 不开心的朋友的数目 。

输入：n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
输出：2
解释：
朋友 1 不开心，因为：
- 1 与 0 配对，但 1 与 3 的亲近程度比 1 与 0 高，且
- 3 与 1 的亲近程度比 3 与 2 高。
朋友 3 不开心，因为：
- 3 与 2 配对，但 3 与 1 的亲近程度比 3 与 2 高，且
- 1 与 3 的亲近程度比 1 与 0 高。
朋友 0 和 2 都是开心的。

不开心的只可能存在于pairs列表中
遍历pairs列表判断
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        int count = 0;
        unordered_map<int, int> m;

        for (auto pair : pairs) {
            m[pair[0]] = pair[1];
            m[pair[1]] = pair[0];
        }

        for (auto pair : m) {

            // 对pair.first,遍历关系近于pair.second的元素
            for (int i = 0; preferences[pair.first][i] != pair.second; i++) {
                /// 近于pair.second的元素
                int temp = preferences[pair.first][i];
                
                /// 近于pair.second的元素, 其pair的位置
                vector<int>::iterator temp_index = find(preferences[temp].begin(), preferences[temp].end(), m[temp] );
                /// 近于pair.second的元素, pair.first的位置
                vector<int>::iterator first_index = find(preferences[temp].begin( ), preferences[temp].end( ), pair.first );
                
                if (first_index < temp_index){
                    count ++;
                    break;
                }
            }  
        }

        return count;
    }
};

int main() {
    vector<vector<int>> preferences = {{1, 2, 3}, {3, 2, 0}, {3, 1, 0}, {1, 2, 0}};
    vector<vector<int>> pairs = {{0, 1}, {2, 3}};

    Solution s;

    cout << s.unhappyFriends(4, preferences, pairs);

    return 0;

}