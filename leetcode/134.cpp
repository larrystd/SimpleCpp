/*
在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明: 

如果题目有解，该答案即为唯一答案。
输入数组均为非空数组，且长度相同。
输入数组中的元素均为非负数。

输入: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

输出: 3
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start_point = -1;
        bool is_start_init = false;
        int length = gas.size();
        int remain_gas = 0;
        int i = 0;
        while(1){
            if (i == start_point || (start_point == ))   // 有可能出不了循环,循环不变量一定设计得尽量简单，便于分析块。
                break;
            if (start_point == -1 && gas[i] > cost[i]){
                start_point = i;
                remain_gas += (gas[i] - cost[i]);
            }
            if (start_point != -1 && remain_gas < 0){
                start_point = -1;   // 重置
                remain_gas = 0;
            }
            i = (i+1) % length;
        }

        return start_point;
    }
};

int main(){
    vector<int> gas = {1,2};
    vector<int> cost = {3,1};
    Solution s;
    cout << s.canCompleteCircuit(gas, cost) <<endl;
    return 0;
}