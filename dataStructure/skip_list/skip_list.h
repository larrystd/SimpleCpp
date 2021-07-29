#ifndef SKIPLIST_H_
#define SKIPLIST_H_

struct skipListNode {
    int key;
    int value;
    skipListNode* next_nodes[];    // 后继指针数组, 柔性数组不计入sizeof(struct), 但可以使用
};

// 跳表
struct skipList_ {
    int level;              // 当前跳表内最大的层数或高度
    skipListNode* head;
};

class SkipList {
private:

    skipList_* slist;

public: 
	// 创建节点
    skipListNode* createNode(int level, int key, int value);

    SkipList();

    // 插入元素的时候所占的层数完全是随机的
    int randomLevel();

    void skipListInsert(int key, int value);

    int skipListSearch(int key);

    int getLevel() const;

    // if (key > node->key)，return true
    bool keyIsGreaterThanNode(const int& key, skipListNode* node) const;

    // 返回大于或等于关键字key的结点中最小的一个结点，如果没有这样的结点，return nullptr
    skipListNode* findGreater_Equal(const int& key) const;

    // 小于key关键字的结点中，最大的那一个
    skipListNode* findLessThanNode(const int& key) const;

    // 返回跳表中的最后一个结点；如果跳表为空，return head
    skipListNode* findLastNode() const;

    // 输出跳表中的数据
    void printSkipList();
};



#endif