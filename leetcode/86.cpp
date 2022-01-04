/*
86 分隔链表

给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你应当 保留 两个分区中每个节点的初始相对位置。

*/

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode (int val) : val(val) {}
};

class List {
public:
    List(vector<int>& list_vals) {
        this->head_ = new ListNode(-1);    // 头节点为虚拟，不储存值
        createList(list_vals);
    } 

    // 根据vector建立链表
    // 尾插法
    void createList(vector<int>& list_vals) {
        ListNode* p = head_;
        for (int i = 0; i < list_vals.size(); i++) {
            ListNode* tmp = new ListNode(list_vals[i]);
            p->next = tmp;
            p = tmp;
        }
    }

    ListNode* head() const {
        return head_;
    }

    void printList() {
        ListNode* p = head_->next;
        while (p) {
            cout << p->val<<" ";
            p=p->next;
        }
    }

    void printList(ListNode* head) {
        ListNode* p = head->next;
        while (p) {
            cout << p->val<<" ";
            p=p->next;
        }
    }

    // 分隔链表
    // 查到某节点，1.删除该节点，2.插入该节点
    // 单向链表，也可重新建一个链表吧

    ListNode* seqaraList(int val, ListNode* head) {
       
        ListNode* left = head;

        while (left->next && left->next->val <val){
                left = left->next;
        }
        ListNode* right_fa = left;
        ListNode* right = left->next;

        while (right) {
            if (right->val < val){
                ListNode* tmp = right;
                right_fa->next = right->next;
                right = right->next;
                
                ListNode* tmp2 = left->next;
                left->next = tmp;
                tmp->next =tmp2;
                left = left->next;
            }else{
                right_fa = right;
                right = right->next;
            }
        }

        return head;
    }

private:
    ListNode* head_;
};

int main() {
    vector<int> my_vec = {2,1};
    List* my_list = new List(my_vec);
    //my_list->printList();

    ListNode* sqara_node = my_list->seqaraList(2,my_list->head());
    my_list->printList(sqara_node);

    return 0;
}