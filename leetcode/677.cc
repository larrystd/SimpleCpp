#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class MapSum {
public:
    unordered_map<string, int> dict;
    MapSum() {
    }
    
    void insert(string key, int val) {
        dict[key] = val;
    }
    
    int sum(string prefix) {

        int result = 0;
        for (auto& pa : dict) {
            if (pa.first.size() < prefix.size())
                continue;
            bool is_exist_prefix = true;
            for (int i = 0; i < prefix.size(); ++i) {
                if (pa.first[i] != prefix[i]) {
                    is_exist_prefix = false;
                    break;
                }
            }
            result = is_exist_prefix ? result+pa.second : result;
        }
        return result;
    }
};

int main() {
    MapSum mapsum;
    mapsum.insert("apple", 3);  
    cout << mapsum.sum("ap") << "\n";           // return 3 (apple = 3)
    mapsum.insert("app", 2);    
    cout << mapsum.sum("app") << "\n";           // return 5 (apple + app = 3 + 2 = 5)

    return 0;
}