/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

最容易想的是用哈希表保存元素出现次数，再用vector转存，对value进行排序。

桶排序
将待排序的序列分到若干个桶中，每个桶内的元素再进行个别排序。
时间复杂度最好可能是线性O(n)，桶排序不是基于比较的排序
*/
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counts;
    int max_count = 0;
    for (const int & num : nums) {
        max_count = max(max_count, ++counts[num]);
    }
    vector<vector<int>> buckets(max_count + 1);
    for (const auto & p : counts) {
        buckets[p.second].push_back(p.first);   //p.second是频次，也就是频次的元素
    }
    vector<int> ans;
    for (int i = max_count; i >= 0 && ans.size() < k; --i) {
        for (const int & num : buckets[i]) {
            ans.push_back(num);
            if (ans.size() == k) {
                break;
            }
        }
    }
    return ans;
}