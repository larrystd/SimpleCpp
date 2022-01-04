/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <iostream>
#include <queue>

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
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        if (!root)
            return false;
        q.push(root->val);
        int level = 0;
        while (!q.empty()) {
            int num = q.size();
            int prev = 0;
            for (int i = 1; i < num; i++) {
                TreeNode* topnode = q.top();
                int topnum = q.top()->val;
                if (level%2 == 0) {
                    if (topnum%2==0 || topnum <= prev)
                        return false;
                }else {
                    if (topnum%2==1 || topnum <= prev)
                        return false;
                }
                if (topnode->left)
                    q.push(topnode->left->val);
                if (topnode->right)
                    q.push(topnode->right->val);
                q.pop();
                prev = topnum;
            }
        }

        return false;
    }
};