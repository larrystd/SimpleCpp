/*
给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

基本思路是用层次遍历，输出每层最右侧的节点
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    void printBinaryTree(TreeNode* p){
        if (!p)
            return;
        cout<<p->val<<" ";
        printBinaryTree(p->left);
        printBinaryTree(p->right);
    }

    // 输出右视图
    vector<int> rightViewTree (TreeNode* p){

        if (!p)
            return vector<int>();
        queue<TreeNode *> q;
        vector<int> right_view;
        q.push(p);
        
        while (!q.empty()){ 
            int level_size = q.size();
            for (int i = 0; i < level_size; i++){
                TreeNode* node = q.front();
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
                if (i == level_size-1)
                    right_view.push_back(node->val);
                q.pop();
            }
        }
        return right_view;
    }

    TreeNode* root;
};

int main() {
    BinaryTree* binary_tree = new BinaryTree;
    // vector<string> tree_array = {"4","9","0","5","1"};
    vector<string> tree_array = {"null"};
    binary_tree->createBinrayTree(tree_array);
    //binary_tree->printBinaryTree(binary_tree->root);
    vector<int> right_view = binary_tree->rightViewTree(binary_tree->root);

    for (vector<int >::iterator iter = right_view.begin(); iter != right_view.end(); iter++){
        cout << *iter<<endl;
    }

    return 0;
}