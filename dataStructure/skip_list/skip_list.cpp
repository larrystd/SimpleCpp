#include <iostream>
#include <cstdlib>
#include "skip_list.h"

const int maxLevel = 12;

skipListNode* SkipList::createNode(int level, int key, int value) {
	/// 之后的level * sizeof(skipListNode*)为柔性数组开辟空间
    skipListNode* node = (skipListNode*)malloc(sizeof(skipListNode) + level * sizeof(skipListNode*));
	node->key = key;
	node->value = value;
		
	return node;
}

/// 构造函数

SkipList::SkipList() {
	slist = (skipList_*)malloc(sizeof(skipList_));
	slist->head = createNode(maxLevel, 0, 0);
	slist->level = 0;

	for (int i = 0; i < maxLevel; i++) {
		slist->head->next_nodes[i] = nullptr;
	}
}

/// 随机高度
int SkipList::randomLevel() {
    int k = 1;
	while (rand() % 2)
		k++;
	k = (k > maxLevel) ? maxLevel : k;

	return k;
}

void SkipList::skipListInsert(int key, int value) {
    skipListNode* update[maxLevel];		// 记录插入的新节点的每一层前驱节点
	skipListNode* p = slist->head;
	skipListNode* q = NULL;
	int k = slist->level;

	//从最高层往下查找需要插入的位置	并更新update
	for (int i = k - 1; i >= 0; i--) {
		while (p->next_nodes[i] != NULL && p->next_nodes[i]->key < key) {
			p = p->next_nodes[i];
		}
		update[i] = p;
	}
	// l0层的next_node
	q = p->next_nodes[0];
	//不能插入相同的key
	if (q && q->key == key) {
		std::cout << "不能插入相同的key！" << std::endl;
		return;
	}

	//产生一个随机层数 k
	//新建一个待插入节点 q，一层一层插入
	int _k = randomLevel();
	//cout << _k << " ";
	//更新跳表的level
	if (_k > slist->level) {
		/// _k层以下的前驱
		for (int i = slist->level; i < _k; i++) {
			update[i] = slist->head;
		}
		// 最大高度
		slist->level = _k;
	}

	/// 创建key, value的节点
	/// 节点层数设置为_k即可, 因为不会再修改层数了
	q = createNode(_k, key, value);
	/// 插入节点q到0~k层
	for (int i = 0; i < _k; i++) {
		q->next_nodes[i] = update[i]->next_nodes[i];
		update[i]->next_nodes[i] = q;
	}
}

/// 根据key得到value
int SkipList::skipListSearch(int key) {
    skipListNode* p = slist->head;
	skipListNode* q = NULL;
	int k = slist->level - 1;

	for (int i = k; i >= 0; i--) {
		while (p->next_nodes[i] != NULL && p->next_nodes[i]->key <= key) {
			if (p->next_nodes[i]->key == key) {
				q = p->next_nodes[i];
				return q->value;
			}
			p = p->next_nodes[i];
		}
	}
	return INT8_MIN;
}

int SkipList::getLevel() const {
    return slist->level;
}

bool SkipList::keyIsGreaterThanNode(const int& key, skipListNode* node) const {
    return ((node != NULL) && (node->key < key));
}

skipListNode* SkipList::findGreater_Equal(const int& key) const {
    skipListNode* tmp = slist->head;
	int level = getLevel() - 1;

	while (true) {
		skipListNode* next = tmp->next_nodes[level];
		if (keyIsGreaterThanNode(key, next)) {
			tmp = next;
		}
		else {
			if (level == 0) {
				return next;
			}
			else {
				level--;
			}
		}
	}
}

skipListNode* SkipList::findLessThanNode(const int& key) const {
    skipListNode* node = slist->head;
	int level = getLevel() - 1;
	while (true) {
		// head比key大, 没有比node小的节点
		if (node != slist->head || node->key >= key) {
			return NULL;
		}
		skipListNode* next = node->next_nodes[level];
		if (next == NULL || next->key >= key) {
			if (level == 0) {
				return node;
			}
			else {
				level--;
			}
		}
		else {
			node = next;
		}
	}
}

/// 找到第0层的最后一个元素
skipListNode* SkipList::findLastNode() const {
    skipListNode* node = slist->head;
	int level = getLevel() - 1;
	while (true) {
		skipListNode* next = node->next_nodes[level];
		if (next == NULL) {
			if (level == 0) {
				return node;
			}
			else {
				level--;
			}
		}
		else {
			node = next;
		}
	}
}

void SkipList::printSkipList() {
    skipListNode* p;
	int k = slist->level;
	/// 分层打印
	for (int i = k-1; i >= 0; i--) {
		p = slist->head->next_nodes[i];
		std::cout << "Level[" << i << "]: ";
		while (p->next_nodes[i] != NULL) {
			std::cout << p->value << " ";
			p = p->next_nodes[i];
		}
		std::cout << p->value << std::endl;
	}
	std::cout << std::endl;
}