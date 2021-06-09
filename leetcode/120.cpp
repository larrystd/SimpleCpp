/*
给定一个三角形 triangle ，找出自顶向下的最小路径和。

每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。

输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int minSumPath (vector<vector<int>> & triangle){
        int num_rows = triangle.size();
        vector<vector<int>> min_path(num_rows);
        min_path[0] = triangle[0];

        for (int row = 1; row < num_rows; row++){
            int num_cols = triangle[row].size();
            min_path[row] = vector<int>(num_cols,0);
            min_path[row][0] = min_path[row-1][0] + triangle[row][0];
            min_path[row][num_cols-1] = min_path[row-1][num_cols-2] + triangle[row][num_cols-1];
            for (int col = 1; col < num_cols-1; col++){
                min_path[row][col] = min(min_path[row-1][col],min_path[row-1][col-1]) + triangle[row][col];
            }
        }
        int min_sum_path = min_path[num_rows-1][0];
        for (int i = 1; i < min_path[num_rows-1].size(); i++){
            min_sum_path = min(min_sum_path, min_path[num_rows-1][i]);
        }
        return min_sum_path;
    }
};

int main(){
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    Solution s;
    cout << s.minSumPath(triangle) <<endl;
    return 0;
}