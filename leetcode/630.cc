// 630. 课程表 III
/*
这里有 n 门不同的在线课程，按从 1 到 n 编号。给你一个数组 courses ，其中 courses[i] = [durationi, lastDayi] 表示第 i 门课将会 持续 上 durationi 天课，并且必须在不晚于 lastDayi 的时候完成。
你的学期从第 1 天开始。且不能同时修读两门及两门以上的课程。
返回你最多可以修读的课程数目。
*/

#include <iostream>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    int size_;
    vector<int> startpoints_;
    vector<int> visited_;
    int lastpoint;

    int result;
    int scheduleCourse(vector<vector<int>>& courses) {
        size_ = courses.size();
        startpoints_.resize(size_);
        visited_.resize(size_);
        lastpoint = 0;
        for (int i = 0; i < size_; i++) {
            startpoints_[i] = courses[i][1]-courses[i][0];
            lastpoint = max(lastpoint, startpoints_[i]);
        }
        result = 0;

        trackback(courses, 0, 0);

        return result;
    }

    void trackback(vector<vector<int>>& courses, int numvisited, int timepoint) {
        result = max(result, numvisited);

        if (timepoint > lastpoint)
            return;

        for (int i = 0; i < size_; i++) {
            if (!visited_[i] && startpoints_[i] >= timepoint) {
                visited_[i] = 1;
                trackback(courses, numvisited+1, timepoint+courses[i][0]);
                visited_[i] = 0;
            }
        }
    }
};

int main() {
    vector<vector<int>> courses =  {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};

    Solution solu;

    cout << solu.scheduleCourse(courses) <<"\n";

    return 0;
}