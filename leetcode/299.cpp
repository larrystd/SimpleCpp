#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
using PAII = pair<char, int>;

class Solution {
public:
    string getHint(string secret, string guess) {
        set<PAII> secret_set;
        unordered_map<char, int> secret_time;

        for (int i = 0; i < secret.size(); i++) {
            secret_set.insert(make_pair(secret[i], i));
            secret_time[secret[i]]++;
        }
        int num_A = 0;
        int num_B = 0;
        
        for (int i = 0; i < guess.size(); i++) {
            if (secret_set.count(make_pair(guess[i], i))){
                num_A++;
                secret_time[guess[i]]--;
            }
        }

        for (int i = 0; i < guess.size(); i++) {
            if (!secret_set.count(make_pair(guess[i], i)) && secret_time[guess[i]]>0) {
                num_B++;
                secret_time[guess[i]]--;
            }
        }

        string res("B");
        if (num_B == 0) {
            res.push_back('0');
        }else {
            while (num_B) {
                res.push_back(num_B%10 + '0');
                num_B /= 10;
            }
        }

        res.push_back('A');
        if (num_A == 0) {
            res.push_back('0');
        }else {
            while (num_A) {
                res.push_back(num_A%10 + '0');
                num_A /= 10;
            }
        }

        reverse(res.begin(), res.end());

        return res;
    }
};

int main() {
    Solution solu;
    string secret = "1122";
    string guess = "1222";
    cout << solu.getHint(secret, guess)<<endl;
    return 0;
}