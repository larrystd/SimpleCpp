#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    unordered_map<vector<int>, int> use_map;

    if (!use_map.count(vector<int>{1,2}))
        use_map[vector<int>{1,2}] = 1;

    return 0;
}