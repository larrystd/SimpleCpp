/*
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (target < matrix[0][0] || target > matrix[m-1][n-1]) {
            return false;
        }
        int p_x;
        int p_y;
        for (p_x = m-1, p_y = n-1; p_x >=0 && p_y >= 0; p_x--, p_y--) {
            if (matrix[p_x][p_y] >= target) {
                if (search_part(p_x, p_y, matrix, target))
                    return true;
            }else{
                break;
            }
        }
        return false;
    }

    bool search_part(int p_x, int p_y, const vector<vector<int>>& matrix, int target) {
        int left = 0, right = p_y;
        while (left <= right) {
            int mid = (left+right) >> 1;
            if (matrix[p_x][mid] == target)
                return true;
            else if(matrix[p_x][mid] < target) 
                left = mid+1;
            else
                right = mid-1;
        }
        left = 0;
        right = p_x;
        while (left <= right) {
            int mid = (left+right) >> 1;
            if (matrix[mid][p_y] == target)
                return true;
            else if(matrix[mid][p_y] < target) 
                left = mid+1;
            else
                right = mid-1;
        }
        return false;
    }
};


int main() {
    Solution solu;
    ///vector<vector<int>> matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
    vector<vector<int>> matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22}};
    cout << solu.searchMatrix(matrix, 14) <<endl;

    return 0;
}