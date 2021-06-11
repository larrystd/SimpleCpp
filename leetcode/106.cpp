/*
根据一棵树的中序遍历与后序遍历构造二叉树。

例如
中序遍历 inorder = [9,3,15,20,7] 左根右
后序遍历 postorder = [9,15,7,20,3] 左右根


思路，先找到根节点，然后根节点左右分两块，循环之。
*/

/*
建立一颗二叉树
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

    // 根据中序遍历和后序遍历重建二叉树
    // 两个vector均有效
    void reconstructBinaryTree(vector<int>& inorderTraverse, vector<int>& postorderTravse){
        int tree_size = inorderTraverse.size();
        TreeNode* root = new TreeNode(postorderTravse[tree_size-1]);

    }

    void dfs(vector<int> inorderTraverse, vector<int> postorderTravse){
        int tree_size = inorderTraverse.size();
        TreeNode* root = new TreeNode(postorderTravse[tree_size-1]);
    }

    TreeNode* root;
};

int main() {
    BinaryTree* binary_tree = new BinaryTree;
    // vector<string> tree_array = {"4","9","0","5","1"};
    vector<string> tree_array = {"1","2","3"};
    binary_tree->createBinrayTree(tree_array);
    binary_tree->printBinaryTree(binary_tree->root);

    return 0;
}