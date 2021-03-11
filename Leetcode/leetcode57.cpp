/*
 * @Author: your name
 * @Date: 2021-03-11 10:50:13
 * @LastEditTime: 2021-03-11 12:44:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /SimpleCode/Leetcode/leetcode57.cpp
 */
#include <iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (newInterval.empty())
            return intervals;
        vector<vector<int>> res;
        if (intervals.empty()){
            res.push_back(newInterval);
            return res;
        }
        
        int start_new = newInterval[0];
        int end_new = newInterval[1];
        vector<int> temp_interval(2,0);
        int i = 0;
        int j = 0;
        while ( i < intervals.size())
        {
            if (start_new >= intervals[i][0] && start_new <= intervals[i][1]){
                temp_interval[0] = intervals[i][0];
                for ( j = i; j < intervals.size(); j++){
                    if (end_new >= intervals[j][0] && end_new <= intervals[j][1]){    // 找到就break
                        temp_interval[1]= intervals[j][1];
                        break;
                    }
                    if (j < intervals.size()-1 && end_new <= intervals[j+1][0] && end_new >= intervals[j][1]){
                        temp_interval[1]= end_new;
                        break;
                    }
                    if (j == intervals.size()-1)
                        temp_interval[1] = end_new;                
                }
                    
                res.push_back(temp_interval);
                i = j+1;
                
            }else{
                res.push_back(intervals[i]);
                i++;
            } 
        }
        return res;
    }
};

int main(){
    Solution *s = new Solution;
    // {{1,3},{6,9}}
    vector<vector<int>> intervals{{1,3},{6,9}};
    vector<int> newInterval{2,5};
    vector<vector<int>> res = s->insert(intervals,newInterval);
    for (int i = 0; i < res.size(); i++){
        for (int j = 0; j < res[i].size(); j++)
            cout <<res[i][j]<<" ";
        cout <<endl;
    }
    return 0;
}