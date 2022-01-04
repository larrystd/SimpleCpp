// 最短补全词
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<int> charcount(26);
        for (char c : licensePlate) {
            if (c >= 'a' && c <= 'z')
                charcount[c-'a']++;
            else if (c >= 'A' && c <= 'Z') 
                charcount[c-'A']++;
        }

        string result;
        int minsize = 0x3f3f3f3f;
        vector<int> tempcharcount(26);
        for (string& word : words) {
            tempcharcount.assign(26, 0);
            for (char c : word) {
                if (c >= 'a' && c <= 'z')
                    tempcharcount[c-'a']++;
                else if (c >= 'A' && c <= 'Z') 
                    tempcharcount[c-'A']++;
            }
            bool iscomplate = true;
            for (int i = 0; i < tempcharcount.size();  i++) {
                if (tempcharcount[i] < charcount[i]) {
                    iscomplate = false;
                    break;
                }
            }
            if (iscomplate && word.size() < minsize) {
                minsize = word.size();
                result = word;
            }   
        }

        return result;
    }
};

int main() {
    Solution solu;
    string licensePlate = "Ah71752";
    vector<string> words = {"suggest","letter","of","husband","easy","education","drug","prevent","writer","old"};
    cout << solu.shortestCompletingWord(licensePlate, words) << "\n";

    return 0;
}