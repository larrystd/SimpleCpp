/// 345. 反转字符串中的元音字母
#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    bool isVowel(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c== 'U')
            return true;
        return false;
    }

    string reverseVowels(string s) {
        int i = 0, j = s.size()-1;

        while (i < j) {
            while (i < j && !isVowel(s[i])) 
                i++;
            
            while (i < j && !isVowel(s[j]))
                j--;
            if (i >= j)
                break;
            char temp;
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;

            i++;
            j--;
        }

        return s;
    }
};

int main() {
    Solution s;
    cout << s.reverseVowels("hell")<<endl;
    return 0;
}