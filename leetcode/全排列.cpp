#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 子集
/// 输出集合的所有子集
class Solution_s {
public:
    vector<vector<int>> res;

    vector<vector<int>> subset(const vector<int>& nums) {
        vector<int> track;
        backtrack(nums, track, 0);
        return res;
    }

    void backtrack(const vector<int>& nums, vector<int>& track, int index) {
        
        res.push_back(track);

        for (int i = index; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(nums, track, i+1);
            track.pop_back();
        }
    }
};

/// 组合
/// 输入两个数字 n, k，算法输出 [1..n] 中 k 个数字的所有组合。

/*
比如输入 n = 4, k = 2，输出如下结果，不能包含重复（按照组合的定义，[1,2] 和 [2,1] 也算重复）：

[
 [1,2],
 [1,3],
 [1,4],
 [2,3],
 [2,4],
 [3,4]
]
*/
class Solution_c {
public:
    vector<vector<int>> res;
    vector<vector<int>> combination(int n, int k) {
        vector<int> track;
        vector<int> nums(n, 0);
        for (int i = 0; i < n; i ++) {
            nums[i] = i+1;
        }
        backtrack(nums, k, track, 0);

        return res;
    }
    void backtrack(vector<int>& nums, int k, vector<int>& track, int index) {
        if (k == 0) {
            res.push_back(track);
            return ;
        }
        for (int i = index; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(nums, k-1, track, i+1);
            track.pop_back();
        }
    }

};

/// 全排列
class Solution_p {
public:

    vector<vector<int>> res;
    vector<vector<int>> permut(const vector<int>& list) {
        vector<int> track;
        traceback(list, track);
        return res;
    }


    void traceback(const vector<int>& list, vector<int>& track) {
        if (list.size() == track.size()) {
            res.push_back(track);
            return;
        }
        for (int i = 0; i < list.size(); i++) {
            if (!count(track.begin(), track.end(), list[i])) {
                track.push_back(list[i]);
                traceback(list, track);
                track.pop_back();
            }
        }
    }
};


/// 括号生成

class Solution_b {
public:
    vector<string> res;
    
    vector<string> generate_bracket(int n) {
        string track;
        backtrack(track, 0,0, n);

        return res;
    }
    void backtrack(string& track, int left_num, int right_num, const int n) {
        if (left_num < right_num)
            return;
        if (left_num == n && right_num == n) {
            res.push_back(track);
            return;
        }

        if (left_num < n) {
            track.push_back('(');
            backtrack(track, left_num+1, right_num, n);
            track.pop_back();
        }
        if (right_num < n) {
            track.push_back(')');
            backtrack(track, left_num, right_num+1, n);
            track.pop_back();
        }
    }
};

int main() {
    //全排列
    
    vector<int> list = {1,3,5,6};

    //Solution_p s;
    //vector<vector<int>> res = s.permut(list);


    //Solution_s s;
    //vector<vector<int>> res = s.subset(list);
    /*
    Solution_c s;
    vector<vector<int>> res = s.combination(4,2);

    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    */

   Solution_b s;
   vector<string> res = s.generate_bracket(3);

   for (int i = 0; i < res.size(); i++) {
       cout << res[i] <<endl;
   }
    return 0;
}