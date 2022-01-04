#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<long, vector<long>, greater<long>> prior_queue;
        prior_queue.push(1);
        set<long> numset;

        long result;
        for (int i = 0; i < n; i++) {
            result = prior_queue.top();
            prior_queue.pop();

            for (int prime : primes) {
                if (!numset.count(prime*result)) {
                    prior_queue.push(prime*result);
                    numset.insert(prime*result);
                }
            }
        }

        return result;
    }

    int nthSuperUglyNumberDP(int n, vector<int>& primes) {

        vector<int> dp(n);
        dp[0] = 1;
        int numprimes = primes.size();
        vector<int> ptrs(numprimes); // 对应primes的指针
        int idx = 1;
        while(idx < n) { 
            int min_ptr = 0;
            long min_value = INT64_MAX;
            for (int i = 0; i < numprimes; i++) {
                long temp = dp[ptrs[i]]*primes[i];
                if (min_value > temp) {
                    min_value=temp;
                    min_ptr = i;
                }
            }
            if (min_value != dp[idx-1]) {
                dp[idx] = min_value;
                idx++;
            } // 有效
            ptrs[min_ptr]++;
        }

        return dp[n-1];
    }


    int nthSuperUglyNumberV3(int n, vector<int>& primes) {
        vector<long> dp(n + 1);
        int numprimes = primes.size();
        vector<int> ptrs(numprimes, 0);
        vector<long> nums(numprimes, 1);    // 记录每个指针下当前乘积
        for (int i = 1; i <= n; i++) {
            long minNum = INT64_MAX;
            for (int j = 0; j < numprimes; j++) {
                minNum = min(minNum, nums[j]);
            }
            dp[i] = minNum;
            for (int j = 0; j < numprimes; j++) {
                if (nums[j] == minNum) {    // 更新所有==minNum的nums[j]
                    ptrs[j]++;
                    nums[j] = dp[ptrs[j]] * primes[j];
                }
            }
        }
        return dp[n];
    }
};

int main() {
    int n = 1000000;
    vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541};
    //int n = 12;
    //vector<int> primes = {2,7,13,19};
    Solution solu;
    cout << solu.nthSuperUglyNumberV3(n, primes) << "\n";
    return 0;
}