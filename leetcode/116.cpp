/*填充每个节点的下一个右侧节点指针
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
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

    Node* connect(Node* root) {
        if (!root)
            return root;
        recursion(root->left, root->right);

        return root;

    }

    void recursion(Node* l, Node* r) {
        if (!l || !r) {
            return;
        }

        l->next = r;

        recursion(l->left, l->right);
        recursion(r->left, r->right);
        recursion(l->right,r->left);
    }



    void printTree(Node* root) {
        while (root) {
            Node* p = root;
            while (p) {
                cout << p->val<< " ";
                p = p->next;
            }
            cout <<"#" <<endl;
            root = root->left;
        }
    }
};

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    BinaryTree* tree;
    Node* root = tree->createTree(nums);
    Node* p = tree->connect(root);
    tree->printTree(p);
    cout << endl;

    return 0;
}