#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() : val(0), left(NULL), right(NULL) {
        cout << "构造"<<endl;
    }

    Node(int _val) : val(_val), left(NULL), right(NULL) {
    }

    Node(int _val, Node* _left, Node* _right)
        : val(_val), left(_left), right(_right) {}

};

class BinaryTree {
public:
    Node* root;

    Node* createTree(const vector<int>& nums) {
        // -1表示null
        cout << nums[0] <<endl;

        //Node* root = new Node(1);
        //this->root = new Node(nums[0]);
        //root -> val = nums[0];
        int val = nums[0];
        Node* proot = new Node(val);
        
        queue<Node*> q;
        q.push(proot);
        int i = 1;
        while (!q.empty()) {
            Node* node = q.front();
            if (node && i < nums.size()) {
                Node* tmp = nums[i] == -1 ? nullptr : new Node(nums[i]);
                node->left = tmp;
                q.push(tmp);
                i++;

                tmp = nums[i] == -1 ? nullptr : new Node(nums[i]);
                node->right = tmp;
                q.push(tmp);
                i++;
            }

            q.pop();
        }

        return proot;
    }


    void printTree(Node* root) {
        queue<Node* > q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                Node* node = q.front();
                int val = node==nullptr ? -1 : node->val;
                cout << val << " ";
                if (node) {
                    q.push(node->left);
                    q.push(node->right);
                }
                q.pop();
            }
        }

    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    BinaryTree* tree;
    Node* root = tree->createTree(nums);
    tree->printTree(root);
    cout << endl;

    return 0;
}