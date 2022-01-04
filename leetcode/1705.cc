#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int result = 0;
        // multiset
        priority_queue<int, vector<int>, greater<int>> p_q;
        int i = 0;  // day
        for (; i < apples.size(); i++) {
            for (int j = 0; j < apples[i]; j++) {   // 要降低优先队列的规模, 用一个pair<int,int>(count, day)来表示,而不是统统加入到队列中
                p_q.push(i+days[i]);
            }
            while (!p_q.empty() && p_q.top() < i+1) {
                p_q.pop();
            }
            if (!p_q.empty()) {
                result ++;
                p_q.pop();
            }
        }

        while (!p_q.empty()) {
            while (!p_q.empty() && p_q.top() < i+1) {
                p_q.pop();
            }
            if (!p_q.empty()) {
                result ++;
                p_q.pop();
            }
            i++;
        }

        return result;
    }
};

int main() {
    vector<int> apples = {1};
    vector<int> days = {2};
    Solution solu;
    cout << solu.eatenApples(apples, days) << "\n";

    return 0;
}

- name: 三叶
    avatar: https://img.moegirl.org.cn/common/thumb/3/39/59088251_p0.jpg/1024px-59088251_p0.jpg
    from: 你的名字
    url: https://zh.moegirl.org.cn/%E5%AE%AB%E6%B0%B4%E4%B8%89%E5%8F%B6
    reason: 不需要理由
- name: 雅人叔
    avatar: https://img.moegirl.org.cn/common/thumb/b/bf/Sakai_Masato.jpg/420px-Sakai_Masato.jpg
    from: 李狗嗨 半泽直树
    url: https://zh.moegirl.org.cn/%E5%A0%BA%E9%9B%85%E4%BA%BA
    reason: 雅人叔~
- name: 千反田爱瑠
    avatar: https://img.moegirl.org.cn/common/thumb/6/68/Chitanda.Eru.full.1053233.jpg/420px-Chitanda.Eru.full.1053233.jpg
    from: 冰菓
    url: https://zh.moegirl.org.cn/%E5%8D%83%E5%8F%8D%E7%94%B0%E7%88%B1%E7%91%A0
    reason: 可爱 白富美~
- name: 古河渚
    avatar: https://img.moegirl.org.cn/common/thumb/f/fc/Nagisa1.jpg/420px-Nagisa1.jpg
    from: Clannad
    url: https://zh.moegirl.org.cn/%E5%8D%83%E5%8F%8D%E7%94%B0%E7%88%B1%E7%91%A0
    reason: Kawai 善解人意~
- name: 立华奏
    avatar: https://img.moegirl.org.cn/common/thumb/8/8c/11258649.png/420px-11258649.png
    from: Angel Beats!
    url: https://zh.moegirl.org.cn/%E7%AB%8B%E5%8D%8E%E5%A5%8F
    reason: 不解释
- name: 宫园薰
    avatar: https://img.moegirl.org.cn/common/thumb/3/3e/Miyazano_Kaori.png/420px-Miyazano_Kaori.png
    from: 四月是你的谎言
    url: https://zh.moegirl.org.cn/%E5%AE%AB%E5%9B%AD%E8%96%B0
    reason: 因为我是友人A
- name: 周杰伦
    avatar: https://img.moegirl.org.cn/common/thumb/a/a8/%E5%91%A8%E6%9D%B0%E4%BC%A6.jpg/420px-%E5%91%A8%E6%9D%B0%E4%BC%A6.jpg
    from: 各种
    url: https://zh.moegirl.org.cn/%E5%91%A8%E6%9D%B0%E4%BC%A6
    reason: 杰伦~青春