/// 5877 检测正方形

/*
给你一个在 X-Y 平面上的点构成的数据流。设计一个满足下述要求的算法：

添加 一个在数据流中的新点到某个数据结构中。可以添加 重复 的点，并会视作不同的点进行处理。
给你一个查询点，请你从数据结构中选出三个点，使这三个点和查询点一同构成一个 面积为正 的 轴对齐正方形 ，统计 满足该要求的方案数目。
轴对齐正方形 是一个正方形，除四条边长度相同外，还满足每条边都与 x-轴 或 y-轴 平行或垂直。

实现 DetectSquares 类：

DetectSquares() 使用空数据结构初始化对象
void add(int[] point) 向数据结构添加一个新的点 point = [x, y]
int count(int[] point) 统计按上述方式与点 point = [x, y] 共同构造 轴对齐正方形 的方案数。

输入：
["DetectSquares", "add", "add", "add", "count", "count", "add", "count"]
[[], [[3, 10]], [[11, 2]], [[3, 2]], [[11, 10]], [[14, 8]], [[11, 2]], [[11, 10]]]
输出：
[null, null, null, null, 1, 0, null, 2]

解释：
DetectSquares detectSquares = new DetectSquares();
detectSquares.add([3, 10]);
detectSquares.add([11, 2]);
detectSquares.add([3, 2]);
detectSquares.count([11, 10]); // 返回 1 。你可以选择：
                               //   - 第一个，第二个，和第三个点
detectSquares.count([14, 8]);  // 返回 0 。查询点无法与数据结构中的这些点构成正方形。
detectSquares.add([11, 2]);    // 允许添加重复的点。
detectSquares.count([11, 10]); // 返回 2 。你可以选择：
                               //   - 第一个，第二个，和第三个点
                               //   - 第一个，第三个，和第四个点
*/

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Point{
public:
    int x;
    int y;
    Point(int x_, int y_) : x(x_), y(y_) {}

    bool operator<(const Point& p) const{
        return this->x < p.x;
    }

    // 供unordered_map使用
    bool operator==(const Point& p) const {
        return this->x == p.x && this->y == p.y; 
    }
};

struct hashPoint {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>() (p.y);
    }
};

class DetectSquares {
public:
    unordered_map<int, vector<Point>> x_map;
    unordered_map<int, vector<Point>> y_map;
    unordered_map<Point,int, hashPoint> points_map;

    DetectSquares() {

    }
    
    void add(vector<int> point) {
        Point p(point[0], point[1]);
        if (points_map.count(p))
            points_map[p]++;
        else
            points_map[p] = 1;

        x_map[point[0]].push_back(p);

        y_map[point[1]].push_back(p);
    }
    
    
    int count(vector<int> point) {
        if (!x_map.count(point[0])) {
            return 0;
        }
        if (!y_map.count(point[1])) {
            return 0;
        }
        int result = 0;

        vector<Point>& x_list = x_map[point[0]];
        vector<Point>& y_list = y_map[point[1]];

        /// 正方形,
        for (int i = 0; i < x_list.size(); i++) {
            for (int j = 0; j < y_list.size(); j++) {
                if (x_list[i].y != point[1] && y_list[j].x != point[0]) {   // 和points不是同一个点
                    if (abs(x_list[i].y - point[1]) == abs(y_list[j].x - point[0])){ /// 临边相等(正方形)
                        Point p(y_list[j].x, x_list[i].y);
                        if (points_map.count(p))  // 存在第三个点
                            result += points_map[p];
                    }
                }
            }
        }

        return result;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */

int main() {
    DetectSquares* detectSquares = new DetectSquares();
    detectSquares->add(vector<int>{3, 10});
    detectSquares->add(vector<int>{11, 2});
    detectSquares->add(vector<int>{3, 2});
    cout << detectSquares->count(vector<int>{11, 10}) <<endl; // 返回 1 。你可以选择：
    cout << detectSquares->count(vector<int>{14, 8})<<endl;  // 返回 0 。查询点无法与数据结构中的这些点构成正方形。
    detectSquares->add(vector<int>{11, 2});    // 允许添加重复的点。
    cout << detectSquares->count(vector<int>{11, 10}) <<endl;
    return 0;
}