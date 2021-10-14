#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int lastRemaining(int n) {
        if (n == 1)
            return 1;
        vector<bool> visited(n);
        int visited_num = 0;
        int i,j;

        while (1) {
            
            i = 0;
            /// 左到右移动
            while (i < n) {
                /// 左侧第一个没有访问的位置
                while (i < n && visited[i]) {
                    i++;
                }
                // 访问
                if (i == n)
                    break;
                /// 找到了，如果是最后一个就return
                if (visited_num == n-1)
                    return i+1;
                visited[i] = true;
                visited_num++;

                // 下一个没有访问的
                while (i < n && visited[i]) {
                    i++;
                }
                if (i == n)
                    break;
                i++;
            }
            /// 右到左移动
            j = n-1;
            while (j >= 0) {
                /// 右侧第一个没有访问的位置

                while (j >= 0 && visited[j]) {
                    j--;
                }
                if (j < 0)
                    break;
                /// 找到了为false的，判断是否为最后一个
                if (visited_num == n-1)
                    return j+1;
                visited[j] = true;
                visited_num++;
                while (j >= 0 && visited[j]) {
                    j--;
                }


                if (i < 0)
                    break;
                j--;
            }
        }
        return 0;

    }
};

class Solution2 {
public:
    int lastRemaining(int n) {
        int last = 0;
        for (int i = 2; i <= n; ++i) {
            (last += m) %= i;   // i为删除前元素数量
        }
        return last;
    }
};

int main() {
    Solution solu;
    cout << solu.lastRemaining(39) <<endl;

    return 0;
}