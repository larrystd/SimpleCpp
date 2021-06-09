/*
给你一个字符串 s ，逐个翻转字符串中的所有 单词 

输入字符串 s 可以在前面、后面或者单词间包含多余的空格。
翻转后单词间应当仅用一个空格分隔。
翻转后的字符串中不应包含额外的空格。

输入：s = "  Bob    Loves  Alice   "
输出："Alice Loves Bob"
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> string_vector;
    string reverseWords (string words){

        string::iterator begin = words.begin();
        string::iterator end = words.end();
        string::iterator word_begin, word_end;
        while (begin != end){
            while (begin != end && isspace(*begin)){
                begin++;
            }
            if (begin == end){
                break;
            }else{
                word_begin = begin;
            }
            while (begin != end && !isspace(*begin)){
                begin++;
            }
            word_end = begin;
            string_vector.push_back(string(word_begin,word_end));
        }

        if (string_vector.size() == 0)
            return string("");
        string ret = "";
        for (int i = string_vector.size()-1; i > 0; i--){
            ret += string_vector[i];
            ret += " ";
        }
        ret+= string_vector[0];
        return ret;

    }
};

int main(){
    string str;
    getline(cin, str);
    Solution s;
    cout << s.reverse_words(str) <<endl;
    return 0;
}