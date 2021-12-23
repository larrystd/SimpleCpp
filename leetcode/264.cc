#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> prior_queue;
        prior_queue.push(1);
        set<long> numset;

        long result;
        for (int i = 0; i < n; i++) {
            result = prior_queue.top();
            prior_queue.pop();
            if (!numset.count(2*result)) {
                prior_queue.push(2*result);
                numset.insert(2*result);
            }

            if (!numset.count(3*result)) {
                numset.insert(3*result);
                prior_queue.push(3*result);
            }
                
            if (!numset.count(5*result)) {
                numset.insert(5*result);
                prior_queue.push(5*result);
            }
            
        }

        return result;
    }

    int nthUglyNumberDP(int n) {

        vector<int> dp(n);
        dp[0] = 1;

        int p1 = 0, p2 = 0, p3 = 0; // 分别表示*2,*3,*5当前的因数对象
        int idx = 1;
        while(idx < n) {
            int temp = min(dp[p1]*2, min(dp[p2]*3, dp[p3]*5));
            if (temp != dp[idx-1]) {
                dp[idx]=temp;
                idx++;
            }
            if (dp[p1]*2 == temp) {
                p1++;
            }
            else if (dp[p2]*3 == temp)
                p2++;
            else if (dp[p3]*5 == temp)
                p3++;
        }

        return dp[n-1];
    }
};

int main() {
    Solution solu;
    cout << solu.nthUglyNumberDP(10) << "\n";
    return 0;
}