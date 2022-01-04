// leetcode 208. 实现 Trie (前缀树)
/*
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

using namespace std;


struct TrieNode {
    char val;
    /// val->node*
    /// map或许可以换成长为26的数组, 数组元素为TrieNode*
    unordered_map<char, TrieNode*> next;
    bool isend;

    TrieNode(char val_):val(val_), isend(false) {}
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        // 根节点不存储
        root = new TrieNode('0');
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root;
        bool isin = true;
        for (char c : word) {
            if (isin && p->next.count(c)) {
                p = p->next[c];
            }else{
                isin = false;
                TrieNode* node = new TrieNode(c);
                p->next[c] = node;
                p = node;
            }
        }
        p->isend = true;
    }
    
    /** Returns if the word is in the trie. */
    /// 区分word还是前缀
    /// 加一个结束标识
    bool search(string word) {
        TrieNode* p = root;
        for (char c : word) {
            if (p->next.count(c)) {
                p = p->next[c];
            }else{
                return false;
            }
        }
        return p->isend;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for (char c : prefix) {
            if (p->next.count(c)) {
                p = p->next[c];
            }else{
                return false;
            }
        }
        return true;
    }

private:
    TrieNode* root;
};

int main() {
    Trie* trie = new Trie();
    trie->insert("apple");
    cout << trie->search("apple") <<" ";   // 返回 True
    cout << trie->search("app") <<" ";     // 返回 False
    cout << trie->startsWith("app") <<" "; // 返回 True
    trie->insert("app");
    cout << trie->search("app") <<" ";     // 返回 True

}