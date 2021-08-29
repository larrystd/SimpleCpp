#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

bool judge(const pair<int,char> a, const pair<int ,char> b) {
    return a.first<b.first;
}
int main()
{
    vector<pair<int ,char>> p;
    p.push_back(make_pair(10,'a'));
    p.push_back(make_pair(9,'c'));
    p.push_back(make_pair(10,'t'));
    p.push_back(make_pair(17,'y'));
    p.push_back(make_pair(10,'b'));
    sort(p.begin(),p.end());
    set<pair<int,char>> s;
    for(auto i=0;i<p.size();i++)
        cout<<p[i].first<<"    "<<p[i].second<<endl;
}