#include<iostream>
using namespace std;

template <typename T>
class AVL{
public:
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
    /// public提供掉private函数的接口
    node* root = NULL;
    int n;
    void insert(T x){
        root=insertUtil(root, x);
    }
    void remove(T x){
        root=removeUtil(root, x);
    }
    node * search(T x){
        return searchUtil(root,x);
    }
    void inorder(){
        inorderUtil(root);
        cout<<endl;
    }

private:
    // tree height
    int height(node* head){
        if (head==nullptr)
            return 0;
        return head->height;
    }

    // AVL左旋和右旋实际上就是处理三个节点的关系
    // 右旋也就所顺时针旋转，左旋逆时针
    // 右旋，本来头节点为head(记A)，变成了head的左子树节点(记B)
    // 同时B的右子树变成了A的左子树，A变成了B的右子树
    // head是旋转轴的根节点
    node * rightRotation(node* head){
        node* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        // 更新节点的高度
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    // 左旋，本来头节点为head(记A)，变成了head的右子树节点(记B)
    // 同时B的左子树变成了A的右子树，A变成了B的左子树
    // 一切操作与右旋相反
    node * leftRotation(node * head){
        node * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    void inorderUtil(node * head){
        if(head==NULL) return ;
        inorderUtil(head->left);
        cout<<head->key<<" ";
        inorderUtil(head->right);
    }

    node * insertUtil(node * head, T x){

        /// 头节点
        if(head==NULL){
            n+=1;
            node * temp = new node(x);
            return temp;
        }
        // 先插入值
        if(x < head->key) head->left = insertUtil(head->left, x);
        else if(x > head->key) head->right = insertUtil(head->right, x);
        // 再更新树高
        head->height = 1 + max(height(head->left), height(head->right));

        // 更新树高后判断是否左旋右旋
        int bal = height(head->left) - height(head->right);
        if(bal>1){  // 左侧高
            if(x < head->left->key){    // 说明元素插入到了左侧，左旋即可
                return rightRotation(head);
            }else{  
                head->left = leftRotation(head->left);  // 插入到右侧，先左旋再右旋转
                return rightRotation(head);
            }

        }else if(bal<-1){
            // 右侧高
            if(x > head->right->key){   // 右侧高插入右子树, 只需要左旋
                return leftRotation(head);
            }else{  // 右侧高插入左子树, 需要先左旋,再右旋
                head->right = rightRotation(head->right);   
                return leftRotation(head);
            }
        }
        return head;
    }

    node* removeUtil(node * head, T x){
        if(head==NULL) return NULL;
        if(x < head->key){
            head->left = removeUtil(head->left, x);
        }else if(x > head->key){
            head->right = removeUtil(head->right, x);
        }else{
        // 将当前节点删除
            node * r = head->right;
            if(head->right==NULL){
                node * l = head->left;
                delete(head);
                head = l;
            }else if(head->left==NULL){
                delete(head);
                head = r;
            }else{
                while(r->left!=NULL) r = r->left;
                head->key = r->key;
                head->right = removeUtil(head->right, r->key);
            }
        }
        if(head==NULL) return head;
        head->height = 1 + max(height(head->left), height(head->right));

        // 删除之后需要更新高度
        int bal = height(head->left) - height(head->right);
        if(bal>1){
            if(height(head->left) >= height(head->right)){
                return rightRotation(head);
            }else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }else if(bal < -1){
            if(height(head->right) >= height(head->left)){
                return leftRotation(head);
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    // 二叉查找树
    node * searchUtil(node * head, T x){
        if(head == NULL) return NULL;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
};

int main(){
    AVL<float> t;
    t.insert(10);
    t.insert(5);
    t.insert(7);
    t.insert(15);
    t.insert(12);
    t.insert(14);
    t.inorder();
}