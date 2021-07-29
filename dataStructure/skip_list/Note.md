#### 柔性数组

```cpp
#include<stdio.h>
typedef struct _SoftArray{
    int len;
    int array[];
}SoftArray;

int main()
{
    int len = 10;

    printf("The struct's size is %d\n",sizeof(SoftArray));
    // 输出 4
    
    SoftArray *p = (SoftArray *)malloc(sizeof(SoftArray) + sizeof(int) * len);

    printf("The struct's size is %d\n",sizeof(SoftArray));
    // 输出还是4


}

```
柔性数组主要用途是为了满足需要变长度的结构体, 本身不占空间, 只是一个偏移量。 柔性数组不算结构体成员，但动态开辟空间时需要加上柔性数组的空间。


#### 跳跃表节点和跳跃表

跳跃表节点记录, 跳跃表对标的是红黑树, 因此它存储key-value节点。可以基于key查找, 插入, 删除。

key, value

每层的连接到next_node的指针
```cpp
struct skipListNode {
    int key;
    int value;
    skipListNode* next_nodes[];    // 后继指针数组, 柔性数组不计入sizeof(struct), 但可以使用
};
```
跳表结构体

记录当前使用的最大level

head指针
```cpp
struct skipList_ {
    int level;              // 当前跳表内最大的层数或高度
    skipListNode* head;
};
```
创建跳跃表节点
```cpp
skipListNode* SkipList::createNode(int level, int key, int value) {
	/// 之后的level * sizeof(skipListNode*)为柔性数组开辟空间
    skipListNode* node = (skipListNode*)malloc(sizeof(skipListNode) + level * sizeof(skipListNode*));
	node->key = key;
	node->value = value;
		
	return node;
}
```
跳跃表的head节点是一个哨兵节点, 不存储数据。尾节点则始终是NULL。数据在中间存储。

#### 插入跳跃表节点

首先定义一个数组, 记录插入节点的每一层的前驱节点`skipListNode* update[maxLevel]`

接着从最高层向下寻找插入的位置, 并更新每一层的update。

产生一个随机层数k, 

依次在0~k层更新, update->插入节点->update的后继节点。

无需拷贝节点, 更改每个节点的next_nodes[]数组链接即可。

```cpp
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
```


#### 查找

跳跃表的查找就是先从最上层开始，找到小于target的最大元素, 若非target。进入下一层查找, 直到到达第0层。

```cpp
int SkipList::skipListSearch(int key) {
    skipListNode* p = slist->head;
	skipListNode* q = NULL;
	int k = slist->level - 1;

	for (int i = k; i >= 0; i--) {
        // 若到达该层小于target的最大元素, 会跳脱循环
		while (p->next_nodes[i] != NULL && p->next_nodes[i]->key <= key) {
			if (p->next_nodes[i]->key == key) {
				q = p->next_nodes[i];
				return q->value;
			}
			p = p->next_nodes[i];   // next_nodes[i]很巧妙
		}
	}
	return INT8_MIN;
}
```


#### 分层打印

```cpp
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
```