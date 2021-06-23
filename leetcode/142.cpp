/*
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

可以使用hash表遍历链表，一旦出现出现过的证明链表有环


快慢指针
使用两个指针，fast 与 slow。它们起始都位于链表的头部。随后，slow 指针每次向后移动一个位置，而 fast 指针向后移动两个位置。
如果链表中存在环，则 fast 指针最终将再次与 slow 指针在环中相遇。

*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    // 建立一个链表，可能是环形链表
public:

    ListNode* createList (vector<int>& vals, int pos) {
        ListNode* head = new ListNode(vals[0]);
        ListNode* p = head;
        for (int i = 1; i < vals.size(); ++i) {
            ListNode* tmp = new ListNode(vals[i]);
            p -> next = tmp;
            p = p->next;
        }
        ListNode* q = head;
        for (int i = 0; i < pos; ++i) {
            q = q->next;
        } 
        p->next = q;
        return head;   
    }

    ListNode *detectCycle(ListNode *head) {
        unordered_map<ListNode* ,int> un_map;
        ListNode *p = head;
        while (p) {
            if (un_map.count(p) == 0) {
                un_map[p] = 1;
            }
            else
                return p;
            p = p->next;
        }
        return nullptr;
    }

};

int main() {
    Solution s;
    vector<int> vals = {3,2,0,-4};
    ListNode* head = s.createList(vals, 1);
    //cout << s.detectCycle(head)->val<<endl;
    return 0;
}