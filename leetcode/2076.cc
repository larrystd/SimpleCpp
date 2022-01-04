/*
leetcode 处理含限制条件的好友请求
给你一个整数 n ，表示网络上的用户数目。每个用户按从 0 到 n - 1 进行编号。

给你一个下标从 0 开始的二维整数数组 restrictions ，其中 restrictions[i] = [xi, yi] 意味着用户 xi 和用户 yi 不能 成为 朋友 ，不管是 直接 还是通过其他用户 间接 。

最初，用户里没有人是其他用户的朋友。给你一个下标从 0 开始的二维整数数组 requests 表示好友请求的列表，其中 requests[j] = [uj, vj] 是用户 uj 和用户 vj 之间的一条好友请求。

如果 uj 和 vj 可以成为 朋友 ，那么好友请求将会 成功 。每个好友请求都会按列表中给出的顺序进行处理（即，requests[j] 会在 requests[j + 1] 前）。一旦请求成功，那么对所有未来的好友请求而言， uj 和 vj 将会 成为直接朋友 。

返回一个 布尔数组 result ，其中元素遵循此规则：如果第 j 个好友请求 成功 ，那么 result[j] 就是 true ；否则，为 false 。

注意：如果 uj 和 vj 已经是直接朋友，那么他们之间的请求将仍然 成功 。

用两个图， 一个表示禁止形成的图, 一个
*/
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <set>

using namespace std;

class Solution {
public:
    bool isInSet(set<int>& myset, int target) {
        if (myset.count(target))
            return true;
        return false;
    }

    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        vector<set<int>> forbit(n);
        vector<vector<int>> graph(n);
        vector<bool> result;
        for (auto& pa : restrictions) {
            forbit[pa[0]].insert(pa[1]);
            forbit[pa[1]].insert(pa[0]);
        }
        deque<int> q;
        for (auto& request : requests) {
            int target = request[0];
            if (isInSet(forbit[target], request[1])) {
                result.push_back(false);
                continue;
            }

            q.clear();
            q.push_back(request[1]);
            bool isaccept = true;
            while (!q.empty() && isaccept) {
                int top = q.front();
                q.pop_front();
                for (auto& near : graph[top]) {
                    if (! isInSet(forbit[target], near))
                        q.push_back(near);
                    else{
                        isaccept = false;
                        break;
                    }
                }
            }
            if (isaccept)
                result.push_back(true);
            else
                result.push_back(false);

        }

        return result;
    }
};

int main() {
    Solution solu;
    vector<vector<int>> restrictions = {{0, 1}};
    vector<vector<int>> requests = {{0,2},{2,1}};

    vector<bool>result = solu.friendRequests(3, restrictions, requests);
    for (auto ele : result) {
        cout << ele << " ";
    }
    return 0;
}