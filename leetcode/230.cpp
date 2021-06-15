/*

给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。

注意二叉搜索树的中序遍历，即左根右即是排序序列、

*/
#include <iostream>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        kth = k;
        inorder(root);
        return res;
    }

private:
    int res = -1;
    int kth = -1;
    void inorder(TreeNode* node) {

        if (node == nullptr || kth < 0) {   // 注意这里的kth<0很重要，剪枝
            return;
        }

        inorder(node -> left);

        if (--kth == 0) {
            res = node -> val;
            return;
        }

        inorder(node -> right);

    }
};