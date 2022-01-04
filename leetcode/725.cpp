#include <iostream>
#include <vector>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* createList(vector<int>& nums) {
        ListNode* head = new ListNode(nums[0]);
        ListNode* p = head;
        
        for (int i = 1; i < nums.size(); i++) {
            ListNode* temp = new ListNode(nums[i]);
            p->next = temp;
            p = temp;
        }

        return head;
    }

    void printList(ListNode* head) {
        ListNode*p = head;
        while (p) {
            cout << p->val<<" ";
            p = p->next;
        }
        cout << endl;
    }

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> result;
        if (head == nullptr)
            return result;
        int len = 0;
        ListNode*p = head;
        while (p) {
            len++;
            p = p->next;
        }
        // 一共是k块, 每块是whole
        int whole = len / k;
        int part = len % k;

        p = head;
        result.resize(k);
        
        for (int i = 0; p && i < k; i++) {
            result[i] = p;
            
            ListNode* q = new ListNode(0);
            ListNode* temp = q;
            q->next = p;
            for (int j = 0; j < whole; j++){
                p=p->next;
                q = q->next;
            }
            if (p &&i < part) {
                p = p->next;
                q = q->next;
            }
            
            q->next = nullptr; 
            delete temp;
            temp = nullptr;
        }
        return result;
    }
};

int main() {
    Solution solu;
    vector<int> input = {1,2,3};
    int k = 5;

    ListNode* head = solu.createList(input);
    solu.printList(head);
    vector<ListNode*> result = solu.splitListToParts(head, k);

    for (auto& it:result) {
        solu.printList(it);
    }
    return 0;
}
