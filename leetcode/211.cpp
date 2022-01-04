#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    vector<TrieNode*> next;
    bool isend;
    TrieNode() :isend(false){
        next.resize(26, nullptr);
    }
};

class WordDictionary {
public:
    TrieNode* root;
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (auto& w : word) {
            if (!node->next[w-'a'])
                node->next[w-'a'] = new TrieNode();
            node = node->next[w-'a'];
        }
        node->isend = true;
    }
    
    /// 查找
    bool search(string word) {
        return dfs(root, word, 0);
    }

    bool dfs(TrieNode* node, string word, int index) {
        if (index == word.size() && node->isend == true)
            return true;
        if (index == word.size() && node->isend == false)
            return false;
        
        bool flag = false;
        for (int i = 0; i < 26; i++) {
            if (node->next[i] && (word[index] == '.' || word[index]-'a'==i))
                flag = flag || dfs(node->next[i], word, index+1);
        }

        return flag;
    }
};

int main() {
    WordDictionary* wordDictionary = new WordDictionary();
    wordDictionary->addWord("bad");
    wordDictionary->addWord("dad");
    wordDictionary->addWord("mad");
    cout << wordDictionary->search("pad") << endl; // return False
    cout << wordDictionary->search("bad") << endl; // return True
    cout << wordDictionary->search(".ad") << endl; // return True
    cout << wordDictionary->search("b..") << endl; // return True

    return false;
}
