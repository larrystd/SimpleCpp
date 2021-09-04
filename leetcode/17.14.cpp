// 设计一个算法，找出数组中最小的k个数。以任意顺序返回这k个数均可。
// 输入： arr = [1,3,5,7,2,4,6,8], k = 4
// 输出： [1,2,3,4]
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        vector<int> res(k,0);
        priority_queue<int, vector<int>, greater<int>> p_q;
        for (int i = 0; i < arr.size(); i++) {
            p_q.push(arr[i]);
        }
        for (int i = 0; i < k; i++) {
            res[i] = p_q.top();
            p_q.pop();
        }
        return res;
    }

    vector<int> smallestK_2(vector<int>& arr, int k) { 
        quicksort(arr, 0, arr.size()-1,k);
        return arr;
    }

    void quicksort(vector<int>& arr, int start, int end, int k) {
        if (start >= end)
            return;
        int i = start, j = end;
        int temp = arr[i];
        while (i < j) {
            // 小于temp的数
            while (i < j && arr[j] >= temp)
                j--;
            if (i < j)
                arr[i] = arr[j];
            // 大于等于
            while (i < j && arr[i] < temp)
                i++;
            if (i < j)
                arr[j] = arr[i];
        }
        arr[i] = temp;
        if (i == k)
            return;
        else if (i > k)
            quicksort(arr,start, i-1,k);
        else  
            quicksort(arr, i+1, end,k);
    }
};


int main() {
    Solution s;
    vector<int> arr = {1,3,5,7,2,4,6,8};
    vector<int> res = s.smallestK_2(arr, 4);
    for (int i = 0; i < res.size(); i++) {
        cout<<res[i] << " ";
    }
    return 0;
}