/*
字典树+回溯

连接词
输入：words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
输出：["catsdogcats","dogcatsdog","ratcatdogcat"]
解释："catsdogcats" 由 "cats", "dog" 和 "cats" 组成; 
     "dogcatsdog" 由 "dog", "cats" 和 "dog" 组成; 
     "ratcatdogcat" 由 "rat", "cat", "dog" 和 "cat" 组成。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TrieNode {
    vector<TrieNode*> next;
    bool end;
    TrieNode()
        : end(false)
    {
        next.assign(26, nullptr);
    }
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort (words.begin(), words.end(), [](string& lhs, string& rhs) {
            return lhs.size() < rhs.size();
        });

        vector<string> result;
        TrieNode* root = new TrieNode;
        TrieNode* p = root;

        for (string& word : words) {
            // 利用Trie 回溯检索是否连接词
            if (dfs(root, 0, word, root))
                result.push_back(word);

            for (int i = 0; i < word.size(); i++) {
                if (!p->next[word[i] - 'a'])
                    p->next[word[i] - 'a'] = new TrieNode;
                p = p->next[word[i] - 'a'];
            }
            p->end = true;
            p = root;
        }

        return result;
    }

    bool dfs(TrieNode* node, int index, string& word, TrieNode* root) { // index表示已经完成的数量

        if (!node)
            return false;
        //if (!node->next[word[index] - 'a']) // 检查完第indx个字符
        //    return false;
        if (node->end && index == word.size())
            return true;
        
        if (node->end) {    // 这里说明到了一个单词, 可以继续向下, 也可以换一个单词
            //node = root;
            bool flag = dfs(node->next[word[index] - 'a'], index+1, word, root) || dfs(root->next[word[index] - 'a'], index+1, word, root);
            return flag;
        }
        return dfs(node->next[word[index] - 'a'], index+1, word, root);
    }
};

int main() {
    //vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    vector<string> words =  {"ag", "da","dag"};

    Solution solu;
    auto result = solu.findAllConcatenatedWordsInADict(words);
    for (auto& word : result) {
        cout << word << "\n";
    }
    return 0;
    // {"ag", "da","dag"};
}