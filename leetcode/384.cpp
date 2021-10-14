/// 打乱数组

/*
给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。

实现 Solution class:

Solution(int[] nums) 使用整数数组 nums 初始化对象
int[] reset() 重设数组到它的初始状态并返回
int[] shuffle() 返回数组随机打乱后的结果
 

示例：

输入
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
输出
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

解释
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。例如，返回 [3, 1, 2]
solution.reset();      // 重设数组到它的初始状态 [1, 2, 3] 。返回 [1, 2, 3]
solution.shuffle();    // 随机返回数组 [1, 2, 3] 打乱后的结果。例如，返回 [1, 3, 2]
*/

#include <vector>
#include <cstdlib>
#include <list>
#include <numeric>
#include <iostream>

using namespace std;

class Solution {
public:
    Solution(vector<int>& nums) {
        srand((unsigned)time(NULL));
        ret.assign(nums.begin(), nums.end());
        ret_back.assign(ret.begin(), ret.end());

        n = nums.size();
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        ret.assign(ret_back.begin(), ret_back.end());

        return ret;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        ret_copy.assign(ret.begin(), ret.end());
        
        int i = n;
        int idx = 0;
        while (i) {
            int r = rand() % i;
            ret[idx++] = ret_copy[r];
            --i;
            ret_copy.erase(ret_copy.begin() + r );
        }
        return ret;
    }


    vector<int> shuffle_2() {

        
        for (int i = n; i > 0; i--){
            //产生[a,b]范围的随机整数公式(rand() % (b-a+1)) + a
            int index = rand() % (i+1); //[0,i]的范围选出index
            int temp = ret[i];
            ret[i] = ret[index];
            ret[index] = temp;
        }
            accumulate
        return ret;
    }


private:
    vector<int> ret_copy;
    vector<int> ret_back;
    vector<int> ret;
    int n;

};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
void printVector(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {1, 2, 3};
    Solution* solution = new Solution(nums);
    vector<int> result = solution->shuffle_2();    // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。例如，返回 [3, 1, 2]
    printVector(result);
    solution->reset();      // 重设数组到它的初始状态 [1, 2, 3] 。返回 [1, 2, 3]
    result = solution->shuffle();    // 随机返回数组 [1, 2, 3] 打乱后的结果。例如，返回 [1, 3, 2]
    printVector(result);
    return 0;

}