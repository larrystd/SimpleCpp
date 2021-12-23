/*
911. 在线选举
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

class TopVotedCandidate {
public:
    unordered_map<int, int> winpersons_;    // 每个时刻的获胜者
    unordered_map<int, vector<int>> votepersons_;   // 每个人的投票时刻
    vector<int> times_;
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        times_.assign(times.begin(), times.end());
        pair<int, int> maxvote(0,0);
        for (int i = 0; i < persons.size(); i++) {
            votepersons_[persons[i]].push_back(times[i]);
            if (votepersons_[persons[i]].size() >= maxvote.second) {    // 平局选时间最近的
                maxvote.first = persons[i];
                maxvote.second = votepersons_[persons[i]].size();
            }
            winpersons_[times[i]] = maxvote.first;
        }
    }
    
    int q(int t) {
        vector<int>::iterator idx = upper_bound(times_.begin(), times_.end(), t);
        return winpersons_[times_[idx-1-times_.begin()]];
    }
};


int main() {
    vector<int> persons = {0, 1, 1, 0, 0, 1, 0};
    vector<int> times = {0, 5, 10, 15, 20, 25, 30};
    TopVotedCandidate topVotedCandidate(persons, times);
    cout << topVotedCandidate.q(3) << "\n"; // 返回 0 ，在时刻 3 ，票数分布为 [0] ，编号为 0 的候选人领先。
    cout << topVotedCandidate.q(12) << "\n"; // 返回 1 ，在时刻 12 ，票数分布为 [0,1,1] ，编号为 1 的候选人领先。
    cout << topVotedCandidate.q(25) << "\n"; // 返回 1 ，在时刻 25 ，票数分布为 [0,1,1,0,0,1] ，编号为 1 的候选人领先。（在平局的情况下，1 是最近获得投票的候选人）。
    cout << topVotedCandidate.q(15) << "\n"; // 返回 0
    cout << topVotedCandidate.q(24) << "\n"; // 返回 0
    cout << topVotedCandidate.q(8) << "\n"; // 返回 1

}