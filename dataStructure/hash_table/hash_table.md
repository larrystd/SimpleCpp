#### 节点
哈希表
hash_table的节点，包含 key键, value值, next指针使用开链, 三个变量。

```cpp
template <class K, class V>
struct HashTableNode {
    K _key;
    V _value;
    HashTableNode<K,V>* _next;
    HashTableNode (const K& key, const V& value)
    : _key(key)
    , _value(value)
    , _next(NULL)
    {}
};
```

#### 哈希表

两个变量, 由节点vector组成的hash表
```cpp
    vector<Node* > _tables; // table是若干hash Node组成的vector
    size_t _size;

    // 初始化
    HashTable(const size_t& capacity)
        : _size(0)
    {
        _tables.resize(13);
    }
```
一般hash表的大小设置为素数。

#### hash函数

一般直接key模capacity
```cpp
template<class K>
struct _HashFunc{
    size_t operator() (const K& key, size_t capacity) {
        return key % capacity;
    }
};
```

#### 插入值

* 使用hash函数计算key的index, 得到_tables[index]
* 判断是否需要开链, 且key不能重复
```cpp
    bool Insert(const K& key, const V& value) {
        /// 使用hash函数计算index
        size_t index = HashFunc() (key, _tables.size());
        Node* cur = _tables[index];
        while (cur) {
            if (cur->_key == key)    // 插入的数据存在于hash表中，key一样
                return false;
            cur = cur->_next;
        }
        Node* NewNode = new Node(key, value);
        NewNode->_next = _tables[index];
        _tables[index] = NewNode;    // 前插法将Node插入链表
        _size++;
    }
```

#### 打印

外层遍历hash表vector
内层遍历链表next
```cpp
    void Print()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				cout << cur->_key << ":" << cur->_value << "->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}
```

