#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size();
        n/=2;
        /// 需要用二维数组
        vector<vector<int>>s(n+1);
        
        int res = INT32_MAX;
        /// 是s[cnt]表示选择了cnt个数, 选择的数和不选择的数的差组成的序列
        /// 例如1110， 表示选择第2，3，4个数与不选第1个数，的差
        for(int i=0; i<1<<n; i++){
            int sum = 0, cnt = 0;
            for(int j=0; j<n; j++){
                if(i>>j&1){
                    sum+=nums[j];
                    cnt++;
                }else {
                    sum-=nums[j];
                }
            }
            s[cnt].push_back(sum);
        }
        
        /// 排序，对每一个选择了cnt的数排序
        for(int i=0; i<s.size(); i++)sort(s[i].begin(), s[i].end());

        /// 处理后半序列，共有1<<n种情况
        for(int i=0; i<1<<n; i++){
            int sum = 0, cnt = 0;
            for(int j = 0; j < n; j++){
                if(i>>j&1){
                    sum+=nums[n+j];
                    cnt++;
                }else {
                    sum-=nums[n+j];
                }
            }
            // 这里有cnt个正号，要到前面取n-cnt个正号的数组匹配 
            /// 从s[n-cnt]里找, s[n-cnt]存储的是选择和不选的差,sum也是选择和不选的差.
            /// 二分查找，找选择和不选差<=0的数
            int l = 0, r = s[n-cnt].size()-1;
            while(l<r){
                int mid = l+r+1>>1;
                /// mid可能是理想值
                if(s[n-cnt][mid] + sum<= 0 )l=mid;
                else r = mid-1;
            }
            /// 目标元素可能是s[n-cnt][mid]<= -sum的最大元素或s[n-cnt][mid]<= -sum的最小元素
            /// s[n-cnt][l]表示还有n-cnt个可以选的条件下的和
            res = min(res, abs(sum + s[n-cnt][l]));
            if(r<s[n-cnt].size()-1)res = min(res, abs(sum + s[n-cnt][r+1]));
        }
        return res;
    }
};

class Solution2 {
public:
    int minimumDifference(vector<int>& nums) {
        int n=nums.size()/2;
        /*
        首先，预处理前n个元素，有2的n次方种状态（即每个元素选或不选），用二进制位的1代表选，0代表不选。
        换句话说，用1代表元素归入第一个数组，用0代表归入第二个数组。
        这里用sum_pre表示前n个数，归为第一个数组的，和归为第二个数组的元素之差。
        */
        vector<int>pre[16];  //pre[i]表示选取i个元素时，和的集合
        for(int i=0;i<(1<<n);i++){
            int sum_pre=0,bit=0;
            for(int j=0;j<n;j++){
                if((i>>j)&1){
                    sum_pre+=nums[j];
                    bit++;
                }else{
                    sum_pre-=nums[j];
                }
            }
            pre[bit].push_back(sum_pre);
        }
        //排序，为了后面二分查找。顺便去重，也可以不去重
        for(int i=0;i<=n;i++){
            sort(pre[i].begin(),pre[i].end());

            /// unique用于去重，其中把重复的元素放到了后面。
            /// 执行完unique()：从容器的开始到返回的迭代器位置的元素是不重复的元素，而从返回的迭代器位置到vector.end()的元素都是没有意义的
            pre[i].erase(unique(pre[i].begin(),pre[i].end()),pre[i].end());
        }

        /*
        考虑后n个数。若后n个数选出bit个归入第一个数组，那么只需从前n个数中拿n-bit个归入第一个数组。
        选数的方式与上面相同，枚举2的n次方个状态。
        对于每个状态，利用二分查找从上面的数组pre[n-bit]中找到一个数k，使得k加上当前的sum_later尽量接近0
        记录下最小的差值即可。
        */
        int ans=1e9+7;
        for(int i=0;i<(1<<n);i++){
            int sum_later=0,bit=0;
            for(int j=0;j<n;j++){
                if((i>>j)&1){
                    sum_later+=nums[j+n];
                    bit++;
                }else{
                    sum_later-=nums[j+n];
                }
            }
            /// lower_bound( begin,end,num)：从pre[n-bit]数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址
            /// n-bit表示还有n-bit可以选
            auto it=lower_bound(pre[n-bit].begin(),pre[n-bit].end(),-sum_later);
            if(it!=pre[n-bit].end())
                ans=min(ans,sum_later+*it);
        }
        return ans;
    }
};


int main() {
    vector<int> nums = {7,3, 3,9};

    Solution2 solu;
    cout << solu.minimumDifference(nums)<<endl;

    return 0;
}