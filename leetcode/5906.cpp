#include <iostream>
#include <string>
#include <string.h>
#include <set>

using namespace std;

class Solution {
public:
    int countValidWords(string sentence) {

        // 根据' '切分字符串
        char* sentence_ch = const_cast<char*> (sentence.c_str());
        set<char> symbol = {'!', ',', '.'};
        //const char* d = " ";
        char* p = strtok(sentence_ch, " ");
        int result = 0;
        while (p) {
            string str(p, strlen(p));
            int len = str.size();
            bool isValid = true;
            if (str[0] == '-' || str[len-1] == '-') // 两边不能是-
                isValid = false;
            if (len >= 2 && str[len-2] == '-' && symbol.count(str[len-1]))  //倒数后两个不能是下划线+标点
                isValid = false;
            int conn = 0;
            for (int i = 0; i < len-1; i++) {
                if (str[i] == '-' && conn > 0){
                    isValid = false;
                    break;
                }
                if (str[i] == '-')
                    conn ++;
                if ((str[i] >= '0' && str[i] <= '9') ||  symbol.count(str[i])){
                    isValid = false;
                    break;
                }  // 数字或者标点
            }
            if (str[len-1] >= '0' && str[len-1] <= '9')    // 最后一个是数字
                isValid = false;
            if (isValid)
                result++;
            p = strtok(NULL, " ");
        }
        return result;
    }
};

int main() {
    string sentence = ", ! a- -b a-b  a-,";
    Solution solu;
    cout << solu.countValidWords(sentence) <<endl;

    return 0;

    
}