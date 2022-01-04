//212 单词搜索2
/*
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
输出：["eat","oath"]

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] 是一个小写英文字母
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] 由小写英文字母组成
words 中的所有字符串互不相同
*/

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    set<string> words_set;
    set<string> ans_set;
    int m;
    int n;
    size_t max_word_len;

    vector<vector<int>> move_list = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));
        max_word_len = 0;
        for (int i=0; i < words.size(); i++) {
            words_set.insert(words[i]);
            max_word_len = max(max_word_len, words[i].size());
        }
        
        string now_words("");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                now_words.push_back(board[i][j]);
                visited[i][j] = 1;
                dfs(i, j, board, visited, words_set, now_words);
                now_words.pop_back();
                visited[i][j] = 0;
            }
        }

        vector<string> result;

        for (set<string>::iterator iter = ans_set.begin(); iter != ans_set.end(); iter++) {
            result.push_back(*iter);
        }

        return result;
    }

    void dfs(int i, int j, vector<vector<char>>& board, vector<vector<int>>& visited, set<string>& words_set, string& now_words) {
        if (now_words.size() > max_word_len)
            return;
        if (words_set.count(now_words)) {
            ans_set.insert(now_words);
        }

        for (auto& p : move_list) {
            int x = i+p[0];
            int y = j+p[1];
            if (x >= 0 && x < m && y >=0 && y < n) {
                if (visited[x][y] == 0) {
                    now_words.push_back(board[x][y]);
                    visited[x][y] = 1;
                    dfs(x,y,board, visited, words_set, now_words);
                    now_words.pop_back();
                    visited[x][y] = 0;
                }

            }
        }

    }
};


int main() {
    // vector<vector<char>> board = {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    vector<vector<char>> board = {{'a','b'}, {'c', 'd'}};
    vector<string> words = {"abcd"};

    Solution solu;
    vector<string> res = solu.findWords(board, words);

    for (auto& str : res) {
        cout << str << "\n";
    }

    return 0;
}