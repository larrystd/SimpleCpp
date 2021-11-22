#include <iostream>
#include<vector>
using namespace std;
vector<int> problem;
void backtrace(vector<int>&problem, vector<vector<char>>& people, int& ans, int valid,int start){
    if(valid ==(int) people[0].size()){
        ans ++;
        return;
    }
    if(start >=(int) people.size())
        return;
    for(int i = start ; i <(int) people.size() ; i ++){
        for(int j = 0 ; j <(int) people[0].size() ; j ++){
            if(people[i][j] == 'n')
                continue;
            problem[j] ++;
            if(problem[j] == 1)
                valid ++;
        }
        backtrace(problem, people, ans, valid, i ++);
        for(int j = 0; j <(int) people[0].size() ; j ++ ){
            if( people[i][j] == 'y')
            {
                if(problem[j] == 1)
                    valid --;
                problem[j]--;

            }
        }
    }
}


int main() {
    int n ;
    cin >> n;

    while(n --){
        int r , c;
        cin >> r >> c;
        vector<vector<char>> people(r, vector<char>(c));
        for(int i = 0 ; i < r ; i ++){
            for(int j = 0 ; j < c ; j ++){
                cin >> people[i][j];
            }
        }
        int ans = 0;
        problem.resize(c);
        backtrace(problem, people,ans, 0,0);
        cout << ans << endl;
    }
    return 0;
}