/*
二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

一个想法是层次遍历，同时用一个map记住当前节点的father节点。

递归的解法呢?

对于最短祖先，则p,q两个节点必然一个在他左子树，一个在右子树
*/
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == NULL) return NULL;           //递归边界
    if(root == p || root == q) return root; // 最近祖先一定为root。

    //分解为求左子树的子问题和右子树的子问题,注意是后序遍历
    TreeNode* left_have = lowestCommonAncestor(root->left,p,q);     
    TreeNode* right_have = lowestCommonAncestor(root->right,p,q);   
    if(left_have && right_have) return root;        //左右子树都有则返回root
    else return left_have ? left_have : right_have;     //如果左右子树中有一个子问题没得到结果，则返回得到结果的子问题.
}