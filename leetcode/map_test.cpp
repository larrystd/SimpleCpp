#include <map>
#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    map<int,int> mp;
    mp[0] = 1;
    cout << mp[0]<<endl;
    cout << mp[1]<<endl;    // 索引直接默认0

    unordered_map<int,int> unorder_mp;
    cout<< unorder_mp[1]<<endl;
    return 0;
}