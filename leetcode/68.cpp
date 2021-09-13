// 68 文本左右对齐
/*
给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

说明:

单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。

确定每一行要放什么单词即可
*/

#include <iostream>
#include <malloc.h>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string substring(vector<string>& words, int begin, int end, int maxWidth) {
        int words_len = 0;
        for (int i = begin; i < end; i++) {
            words_len += words[i].size();
        }
        int space_len = maxWidth - words_len;
        string ret("");
        if (end - begin == 1){
            ret.append(words[begin]);
            ret.append(space_len, ' ');
            return ret;
        }

        int whole_space = space_len / (end - begin-1);
        int leave_space = space_len % (end - begin-1);


        int count_whole = 0;
        for (int i = begin; i < end-1; i++) {
            ret.append(words[i]);
            ret.append(whole_space, ' ');
            if (count_whole < leave_space)
                ret.push_back(' ');
            count_whole++;
        }
        ret.append(words[end-1]);

        return ret;
    }

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int sum_len = 0;
        int begin = 0;
        int end = 0;

        for (int i = 0; i < words.size(); i++) {
            if (sum_len + words[i].size() <= maxWidth){
                sum_len += words[i].size();
                end++;
                sum_len ++; // 一个空格
            }else {
                result.emplace_back(substring(words, begin, end, maxWidth));
                // 另起一行
                sum_len = 0;
                begin = end;
                sum_len += words[i].size();
                end++;
                sum_len ++; // 一个空格
            }
        }
        // 应该是最后一行要处理, begin 到end
        string last_word("");
        int count_char = 0;
        for (int i = begin; i < end-1; i++) {
            last_word.append(words[i]);
            last_word.push_back(' ');
            count_char+= words[i].size()+1;
        }
        last_word.append(words[end-1]);
        count_char+= words[end-1].size();
        last_word.append(maxWidth-count_char, ' ');

        result.emplace_back(last_word);
        return result;
    }
};

int main() {
    string s("");
    s.append(5, ' ');
    cout << s<< "\n";
    cout << s.size() <<endl;
    s.append("123");
    cout << s << "\n";
    cout << s.size() <<endl;

    vector<string> words_1 = {"This", "is", "an", "example", "of", "text", "justification."};
    vector<string> words_2 = {"What","must","be","acknowledgment","shall","be"};
    vector<string> words_3 = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    vector<string> words_4 = {"This"};
    vector<string> words_5 = {"This", "is"};
    Solution solution;
    vector<string> result = solution.fullJustify(words_5, 16);

    for (string& res : result) {
        cout << res <<endl;
        cout << res.size() <<endl;
    }

    return 0;
}