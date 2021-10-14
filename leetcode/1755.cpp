#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int half = n / 2;
        int ls = half, rs = n - half;
        
        /// 所有的挑选情况， 集合
        vector<int> lsum(1 << ls, 0);
        for (int i = 1; i < (1 << ls); i++) {
            for (int j = 0; j < ls; j++) {
                /// (i & (1 << j)) == 0
                /// 基于二进制的选择, 然后求和
                if ((i & (1 << j)) == 0) continue;
                lsum[i] = lsum[i-(1<<j)] + nums[j];
                break;
            }
        }
        vector<int> rsum(1 << rs, 0);
        for (int i = 1; i < (1 << rs); i++) {
            for (int j = 0; j < rs; j++) {
                if ((i & (1 << j)) == 0) continue;
                rsum[i] = rsum[i-(1<<j)] + nums[ls+j];
                break;
            }
        }

        //// 每个选择的求和排序
        sort(lsum.begin(), lsum.end());
        sort(rsum.begin(), rsum.end());
        
        /*
        原数组的一个子序列和，必然为下列三者之一：
        lsum 中的某个元素；
        rsum 中的某个元素；
        lsum 中的某个元素与 rsum 中的某个元素之和。
        */
        int ret = INT32_MAX;
        for (int x: lsum) {
            ret = min(ret, abs(goal - x));
        }
        for (int x: rsum) {
            ret = min(ret, abs(goal - x));
        }
        
        /// 同时处理两个数组
        int i = 0, j = rsum.size() - 1;
        while (i < lsum.size() && j >= 0) {
            /// 二分查找
            int s = lsum[i] + rsum[j];
            ret = min(ret, abs(goal - s));
            if (s > goal) {
                j--;
            } else {
                i++;
            }
        }
        return ret;
    }
};

const int N = 2e6;
class Solution2 {
public:
    vector<int> q;

    int n,cnt,goal,res;
    /// dfs得到前半段的所有情况
    void dfs1(vector<int>& nums,int idx,int sum)
    {
        // 找到一个可行解
        if(idx==(n+1)/2)// n向上取整，前半部分为[0,n/2]
        {
            q[cnt++]=sum;
            return;
        }
        // 枚举两种情况，一种是选上第idx个元素，另一种是不选第idx个元素
        dfs1(nums,idx+1,sum);
        dfs1(nums,idx+1,sum+nums[idx]);
    } 

    void dfs2(vector<int>& nums,int idx,int sum)
    {
        // 找到一个可行解
        if(idx==n)// 后半部分为[n/2+1,n-1]
        {
            /// cnt是前半段所有情况的大小
            int l=0,r=cnt-1;
            // 二分查找再前半段q中找到使q[mid]+sum最逼近goal的位置(<= goal)
            while(l<r)
            {
                // 向上取整，避免 left 取不到 right 造成死循环
                int mid=(l+r)>>1;
                /// 当前的sum加前半段的值
                if(q[mid]+sum <= goal) l=mid;// mid满足check，向右逼近，mid可能就是目标值，所以l=mid
                else r=mid-1;// mid不满足check，向左逼近，mid不可能为目标值，所以r=mid-1
            }
            // 最后找到的元素为最接近goal的
            res=min(res,abs(q[r]+sum-goal));
            // 若r有下一个元素，那么我们最近goal的元素要么在 <=goal 的最大位置产生，要么在 >goal 的最小位置产生
            // 所以每次更新res时，注意这两个位置
            if(r+1<cnt)
                res=min(res,abs(q[r+1]+sum-goal));
            return;
        }
        // 遍历后半段，枚举两种情况，一种是选上第idx个元素，另一种是不选第idx个元素
        dfs2(nums,idx+1,sum);
        dfs2(nums,idx+1,sum+nums[idx]);
    }
    
    // 题解：双向dfs，dfs1枚举2^20中选法，然后排序前半段得到的子序列和数组，然后再枚举后半段的子序列，二分前半段的子序列和数组，使得前半段的子序列和与后半段的子序列和相加的结果接近goal
    int minAbsDifference(vector<int>& nums, int _goal) {
        q.resize(N);
        n=nums.size(),cnt=0,goal=_goal,res=INT32_MAX;
        // 先搜索前一半，给搜索完的数组排个序，便于在搜索后一半数组的时候进行二分
        dfs1(nums,0,0);
        /// 排序
        sort(q.begin(),q.begin()+cnt);
        // 搜索后一半
        dfs2(nums,(n+1)/2,0);
        return res;
    }
};

int main() {
    vector<int> nums = {7,-9,15,-2};
    int goal = -5;

    Solution2 solu;
    cout << solu.minAbsDifference(nums, goal);

    return 0;
}

