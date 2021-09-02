/*
建立一颗二叉树
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0) {}
    TreeNode(int val) : val(val) {}
}TreeNode;

class BinaryTree {
public:
    // 一个vector储存层次遍历的二叉树
    // tree_array有效
    TreeNode* root;
    TreeNode* createBinrayTree(vector<string>& tree_array){
        queue<TreeNode* > q;
        root = new TreeNode(atoi(tree_array[0].c_str()));
        q.push(root);
        int i = 1;
        while (i < tree_array.size() && !q.empty()){
            TreeNode* p = q.front();
            if (tree_array[i] == "null"){
                p->left = nullptr;
            }else{
                p->left = new TreeNode(atoi(tree_array[i].c_str()));
                q.push(p->left);
            }
            i++;
            if (i == tree_array.size() || tree_array[i] == "null"){
                p->right = nullptr;
            }else{
                p->right = new TreeNode(atoi(tree_array[i].c_str()));
                q.push(p->right);
            }
            i++;
            q.pop();
        }
        return root;
    }

    // 打印二叉树
    // 前序遍历，永远打印根节点
    // 根左右遍历
    void preorder(TreeNode* p){
        if (!p)
            return;
        cout<<p->val<<" ";
        preorder(p->left);
        preorder(p->right);
    }

    // 栈实现 前序遍历
    void preorder_stack(TreeNode* root) {
        stack<TreeNode* > sta;
        TreeNode* p = root;

        while (p != nullptr || !sta.empty()) {
            while (p != nullptr) {  /// 直到搜索到没有左孩子的根节点
                cout << p->val << " ";
                sta.push(p);    // 栈里面都是节点
                p = p->left;
            }
            /// 处理右节点
            if (!sta.empty()) {
                p = sta.top();
                sta.pop();      // 退栈
                p = p->right;
            }
        }
    }


    // 中序遍历
    void inorder(TreeNode* p){
        if (!p)
            return;
        
        inorder(p->left);
        cout<<p->val<<" ";
        inorder(p->right);
    }

    // 栈实现 前序遍历
    void inorder_stack(TreeNode* root) {
        stack<TreeNode* > sta;
        TreeNode* p = root;

        while (p != nullptr || !sta.empty()) {
            while (p != nullptr) {
                sta.push(p);    // 栈里面都是节点
                p = p->left;
            }
            if (!sta.empty()) {
                p = sta.top();
                cout << p->val << " "; // 退栈时打印
                sta.pop();      // 退栈
                p = p->right;   // 处理右节点
            }
        }
    }


    
};

int main() {
    BinaryTree* binary_tree = new BinaryTree;
    // vector<string> tree_array = {"4","9","0","5","1"};
    // 层次遍历输入每个节点值
    vector<string> tree_array = {"2","7","5", "4", "6", "null", "9", "null", "null", "5", "11", "4", "null"};
    /*
                2
            7               5
        4       6       null        9
    null null 5  11             4           null
    */
    binary_tree->createBinrayTree(tree_array);
    cout << "preorder traverse" <<endl;
    binary_tree->preorder(binary_tree->root);
    cout << endl;
    binary_tree->preorder_stack(binary_tree->root);
    cout << endl;
    cout << "inorder traverse" <<endl;
    binary_tree->inorder(binary_tree->root);
    cout << endl;
    binary_tree->inorder_stack(binary_tree->root);


    return 0;
}