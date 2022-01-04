#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int nextstep(int index, int n, vector<int>& nums) {
        return ((index + nums[index])%n + n) % n;
    }

    bool circularArrayLoop(vector<int>& nums) {
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            int slow = i;
            int fast = nextstep(slow, len, nums);

            
            // 方向一致且不为0
            while (nums[fast] * nums[i] > 0 && nums[nextstep(fast, len, nums)] * nums[i] > 0) {
                if (slow == fast) {
                    if (slow == nextstep(slow, len, nums))
                        break;
                    return true;
                }
                slow = nextstep(slow, len, nums);
                // 快指针走两次, 慢指针走一次
                fast = nextstep(nextstep(fast, len, nums), len, nums);
            }
        }
        return false;
    }


    // 朴素模拟
    int n;
    vector<int> nums;
    bool circularArrayLoop_2(vector<int>& _nums) {
        nums = _nums;
        n = nums.size();
        for (int i = 0; i < n; i++) {
            if (check(i)) return true;
        }
        return false;
    }
    bool check(int start) {
        int cur = start;
        bool flag = nums[start] > 0;
        int k = 1;
        while (true) {
            if (k > n) return false;
            int next = ((cur + nums[cur]) % n + n ) % n;
            if (flag && nums[next] < 0) return false;
            if (!flag && nums[next] > 0) return false;
            if (next == start) return k > 1;
            cur = next;
            k++;
        }
    }
};

int main() {
    vector<int> vect = {-2,-3,-9};
    Solution s;
    //cout << (-10 % 3) <<endl;
    cout << s.circularArrayLoop_2(vect)<<endl;
    return 0;
}