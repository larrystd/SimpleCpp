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

    // 从根节点到叶节点的数字之和
    // dfs
    int sumRootLeaf (){
        vector<string> numbers;
        string number = string("");
        dfs(numbers, number, root);
        /*
        for (vector<string>::iterator iter = numbers.begin(); iter != numbers.end(); iter++){
            cout << *iter <<endl;
        }
        */
        string sum_string = string("");
        for (vector<string>::iterator iter = numbers.begin(); iter != numbers.end(); iter++){
            sum_string = sumString(sum_string,*iter);
        }

        return atoi(sum_string.c_str());
    }

    string sumString (string& s1, string& s2){
        string sum_string;
        int up = 0;
        int i,j;
        for (i = s1.size() - 1, j = s2.size() - 1; i >=0 && j >=0; i--,j--){
            int sum_s = up + s1[i] - '0' + s2[j] - '0';
            sum_string.push_back(sum_s %10 + '0');
            up = sum_s/10;
        }
        while (i >= 0){
            int sum_s = up+s1[i] - '0';
            sum_string.push_back(sum_s %10 + '0');
            up = sum_s/10;
            i--;
        }
        while (j >= 0){
            int sum_s = up+s2[j] - '0';
            sum_string.push_back(sum_s %10 + '0');
            up = sum_s/10;
            j--;
        }
        if (up == 1){
            sum_string.push_back(up + '0');
        }
        reverse(sum_string.begin(), sum_string.end());
        return sum_string;
    }

    void dfs(vector<string>& numbers, string& number, TreeNode* node){

        number.push_back('0'+node->val);
        if (!node->left && !node->right){
            numbers.push_back(number);
            return;
        }
        if (node->left){
            dfs(numbers, number, node->left);
            number.pop_back();
        }
        if (node->right){
            dfs(numbers, number, node->right);
            number.pop_back();
        }
    }



    TreeNode* root;
};

int main() {
    BinaryTree* binary_tree = new BinaryTree;
    // vector<string> tree_array = {"4","9","0","5","1"};
    vector<string> tree_array = {"1","2","3"};
    binary_tree->createBinrayTree(tree_array);
    binary_tree->printBinaryTree(binary_tree->root);

    cout << binary_tree->sumRootLeaf() <<endl;

    return 0;
}