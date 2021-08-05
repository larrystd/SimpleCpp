#### node节点

node节点主要变量有, value, height, left和right子树指针。

```cpp
    class node{
    public:
        T key;
        int height;
        node * left;
        node * right;
        node(T k){
            height = 1;
            key = k;
            left = NULL;
            right = NULL;
        }
    };
```


#### 遍历

以中序遍历为例, 直接递归

```cpp
    void inorderUtil(node * head){
        if(head==NULL) 
            return ;
        inorderUtil(head->left);
        cout<<head->key<<" ";
        inorderUtil(head->right);
    }
```

#### 插入

与链表不同的, 二叉树不用预先设置哨兵节点, 也就是说root节点也可以直接放在insert函数中。

插入过程可以可以总结为
* 递归的, 每次递归是二叉树的一层
* 先插入节点,寻找位置这样递归到栈顶
* 插入完节点, 递归即开始返回, 每次更新head高度(level最低的为1)
* 对当前的节点, 根据左右子树高度, 判断是否需要左旋右旋

```cpp
    node * insertUtil(node * head, T x){

        /// 找到插入的位置
        if(head==NULL){
            n+=1;
            node * temp = new node(x);  // height = 1
            return temp;
        }
        // 先插入值
        if(x < head->key) head->left = insertUtil(head->left, x);
        else if(x > head->key) head->right = insertUtil(head->right, x);
        // 更新树高
        head->height = 1 + max(height(head->left), height(head->right));

        // 判断是否左旋右旋, 根据子树的高度
        int bal = height(head->left) - height(head->right);
        // bal绝对值大于1, 需要左旋右旋
        if(bal>1){ // 左侧高>1, 说明元素插到head的左子树下
            
            if(x < head->left->key){    // 左侧高>1情况下, 元素插到左子树的左孩子之下
                return rightRotation(head); // 右旋
            }else{      /// 左侧高>1情况下, 元素插到左子树的右孩子之下
                head->left = leftRotation(head->left);  // 以左子树为轴左旋
                return rightRotation(head); // 再右旋
            }

        }else if(bal<-1){   // 左侧高>1, 说明元素插到了右子树之下
            if(x > head->right->key){   // 插到了右子树的右孩子下面
                return leftRotation(head);  // 左旋
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
```

#### 右旋

以head为轴右旋

* 设置newhead， 即head->left
* head左子树重新设置为newhead的右子树、
* newhead的右子树设置为head
* 更新head和new_head的树高( 注意除了head和newhead, 其余节点树高是不变的, 而任何节点的高度可以写成1+max(height(head->left), height(head->right)))
* return newhead

```cpp
    node * rightRotation(node* head){
        node* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        // 更新节点的高度
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }
```

同样以head为节点左旋

```cpp
    node * leftRotation(node * head){
        node * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }
```