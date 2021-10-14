#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int edge_len;
    bool makesquare(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (auto& num : nums) {
            sum += num;
        }
        if (sum % 4 != 0)
            return false;
        edge_len = sum/4;

        int num_edge = 0;

        vector<int> select_node;
        set<int> visited_node;

        /*
        for (int i = 0; i < nums.size(); i++) {
            if (visited_node.count(i))
                continue;
            select_node.push_back(i);
            dfs(i, nums, num_edge, nums[i], visited_node, select_node);
            select_node.pop_back();
        }
        */

        dfs(0, nums, num_edge, nums[i], visited_node, select_node);

        return num_edge == 4;

    }

    bool dfs(int index, vector<int>& nums, int& num_edge, int cur_len, set<int>& visited_node, vector<int>& select_node) {
        if (cur_len > edge_len)
            return false;
        if (cur_len == edge_len){
            num_edge++;
            /// 访问过的点
            for (auto& node : select_node) {
                visited_node.insert(node);
            }
            return true;
        }
        bool flag = true;
        for (int i = index; i < nums.size(); i++) {
            if (visited_node.count(i))
                continue;
            select_node.push_back(i);
            flag = flag && dfs(i+1, nums, num_edge, cur_len+nums[i], visited_node, select_node);
            select_node.pop_back();

        }
        return flag;
    }
};


class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        int sum=0;
        for(int num:matchsticks){
            sum+=num;   /// 求和
        }
        if(sum%4!=0)return false;

        vector<int>adds(4,0);   /// 记录每条边的长度
        sort(matchsticks.begin(),matchsticks.end(),greater<int>());     /// 从大到小排序
        return dfs(0,adds,matchsticks,sum);
    }
    bool dfs(int index,vector<int>&adds,vector<int>&matchsticks,int sum){
        if(*max_element(adds.begin(),adds.end()) > sum/4)return false;
        if(index ==matchsticks.size()){
            /// 四条边一样
            if(adds[0]==adds[1]&&adds[1]==adds[2]&&adds[2]==adds[3]){
                //cout<<beg<<' '<<adds[0]<<' '<<adds[1]<<' '<<adds[2]<<' '<<adds[3]<<endl;
                return true;
            }
            else return false;
        }
        for(int i=0;i<4;i++){   /// 四条边选择火柴, 每个火柴有四种决策
            adds[i]+=matchsticks[index];  /// 选择火柴
            if(dfs(beg+1,adds,matchsticks,sum))return true;
            adds[i]-=matchsticks[index];
        }
        return false;
    }
};

int main() {
    vector<int> nums = {10,6,5,5,5,3,3,3,2,2,2,2};
    Solution solu;

    cout << solu.makesquare(nums) <<endl;

    return 0;
}