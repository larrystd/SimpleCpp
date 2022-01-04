#include <queue>
#include <vector>
#include <functional>
#include <stdlib.h>

using namespace std;


class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        int n = nums.size();

        auto op1 = [](int x, int y) -> int { return x + y; };
        auto op2 = [](int x, int y) -> int { return x - y; };
        auto op3 = [](int x, int y) -> int { return x ^ y; };

        vector<function<int(int, int)>> ops = {op1, op2, op3};

        vector<int> vis(1001, 0);
        queue<pair<int, int>> q;
        q.emplace(start, 0);    // 从start开始, step = 0
        vis[start] = 1;
        while (!q.empty()) {
            auto [x, step] = q.front();
            q.pop();
            // 枚举数组中的元素
            for (int i = 0; i < n; i++) {
                for (auto& op : ops) {
                    int nx = op(x, nums[i]);    // 计算op(x和nums), 转化情况x->nx
                    if (nx == goal) {
                        return step+1;
                    }
                    // 如果nx越过0或1000, 不能继续执行运算
                    if (nx >= 0 && nx <= 1000 && !vis[nx]) {
                        vis[nx] = 1;
                        q.emplace(nx, step+1);  // 加入队列, 使nx有机会继续转化
                    }
                }
            }
        }

        return -1;
    }


    int minimumOperations(vector<int>& nums, int start, int goal) {
        int n = nums.size();
        auto op1 = [](int x, int y) -> int { return x + y; };
        auto op2 = [](int x, int y) -> int { return x - y; };
        auto op3 = [](int x, int y) -> int { return x ^ y; };
        vector<function<int(int, int)>> ops = {op1, op2, op3};   // 运算符列表
        vector<int> vis(1001, 0);   // 可操作范围内整数的访问情况
        queue<pair<int, int>> q;
        q.emplace(start, 0);
        vis[start] = 1;
        while (!q.empty()){
            auto [x, step] = q.front();
            q.pop();
            // 枚举数组中的元素和操作符并计算新生成的数值
            for (int i = 0; i < n; ++i){
                for (auto& op: ops){
                    int nx = op(x, nums[i]);
                    // 如果新生成的数值等于目标值，则返回对应操作数
                    if (nx == goal){
                        return step + 1;
                    }
                    // 如果新生成的数值位于可操作范围内且未被加入队列，则更改访问情况并加入队列
                    if (nx >= 0 && nx <= 1000 && !vis[nx]){
                        vis[nx] = 1;
                        q.emplace(nx, step + 1);
                    }
                }
            }
        }
        // 不存在从初始值到目标值的转化方案
        return -1;
    }
};

int main() {
    char* c = malloc(1);
    free(c)
}