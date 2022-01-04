/*

排序链表
链表的归并排序

递归排序三部曲：1，快慢指针找中点；2，递归调用mergeSort，3，合并两个链表

*/

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode (int val) : val(val) {}
};

class Solution {
public:
    // 根据vector建立链表
    // 尾插法
    ListNode* createList(vector<int>& list_vals) {
        ListNode* head = new ListNode(list_vals[0]);
        ListNode* p = head;
        for (int i = 1; i < list_vals.size(); i++) {
            ListNode* tmp = new ListNode(list_vals[i]);
            p->next = tmp;
            p = tmp;
        }
        return head;
    }

    void printList(ListNode* head) {
        ListNode* p = head;
        while (p) {
            cout << p->val<<" ";
            p=p->next;
        }
        cout << endl;
    }
    ListNode* sortList(ListNode* head) {
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return head;
        }
        if (head->next == tail) {   // 结尾不可到达
            head->next = nullptr;
            return head;
        }
        ListNode* slow = head, *fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) { 
                fast = fast->next;
            }
        }
        ListNode* mid = slow;
        return merge(sortList(head, mid), sortList(mid, tail)); // 分治，两个有序的合并成为新的有序
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        // 归并排序,merge需要额外空间
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};

int main() {
    Solution s;
    vector<int> vec = {4,2,1,3};
    ListNode* head = s.createList(vec);
    s.printList(head);
    ListNode* sort_head= s.sortList(head);
    s.printList(sort_head);

    return 0;
}