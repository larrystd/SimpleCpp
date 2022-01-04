/*
leetcode 周赛
游戏中弱角色的数量

你正在参加一个多角色游戏，每个角色都有两个主要属性：攻击 和 防御 。给你一个二维整数数组 properties ，其中 properties[i] = [attacki, defensei] 表示游戏中第 i 个角色的属性。

如果存在一个其他角色的攻击和防御等级 都严格高于 该角色的攻击和防御等级，则认为该角色为 弱角色 。更正式地，如果认为角色 i 弱于 存在的另一个角色 j ，那么 attackj > attacki 且 defensej > defensei 

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;


class Solution {
public:

    /// 按照攻击从大到小，攻击相同，防御从小到大排序
    /// 顺序遍历, 维护遍历过的防御最大, 若当前小于该防御则攻击亦必然小于之(因为攻击相同按防御从小打到排序)
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        int n = properties.size();
        sort(properties.begin(), properties.end(), [](auto& a, auto& b) {
            return a[0] > b[0] || (a[0] == b[0]) && (a[1] < b[1]);
        });

        int count = 0;
        int max_def = properties[0][1];

        for (vector<int> p : properties) {
            if (p[1] < max_def)
                count++;
            else
                max_def = p[1];
        }
        
        return count;
    }


    int numberOfWeakCharacters_2(vector<vector<int>>& properties) {
        int n = properties.size();
        vector<int> index(n, 0);
        for(int i = 0; i < n; i++) {
            index[i] = i+1;
        }
        sort(properties.begin(), properties.end(), [](auto& a, auto& b) {
            return a[0] > b[0];
        });


        int count = 0;
        vector<int> flag(n,0);
        //vector<int> max_v = properties[0];
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j<n; j++){
                if (properties[i][0] > properties[j][0] && properties[i][1] > properties[j][1]){
                    if (flag[j] == 0){
                        count++;
                        flag[j]=1;
                    }
                }
            }
        }
        return count;
    }
};

        /*
        vector<int> dp(n,0);

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < i; j++) {
                if (properties[j][0] > properties[i][0] && properties[j][1] > properties[i][1])
                    dp[j] = dp[j]+1;
            }
        }

        return *max_element(dp.begin(), dp.end());
        */


int main() {
    //vector<vector<int>> nums = {{1,5},{10,4},{4,3}};
    //vector<vector<int>> nums ={{7,7},{1,2},{9,7},{7,3},{3,10},{9,8},{8,10},{4,3},{1,5},{1,5}};
    //[[7,7],[1,2],[9,7],[7,3],[3,10],[9,8],[8,10],[4,3],[1,5],[1,5]]
    
    vector<vector<int>> nums = {{7,9},{10,7},{6,9},{10,4},{7,5},{7,10}};
    Solution s;
    cout << s.numberOfWeakCharacters(nums) <<endl;
    return 0;
}