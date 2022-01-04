 
  #include <vector>
  #include <queue>
  #include <iostream>

  using namespace std;
  
  struct ListNode {
      int val;
      ListNode* next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode* next) : val(x), next(next) {}
  };


class complist {
    public:
        bool operator() (const ListNode* l, const ListNode* r) {
            return l->val > r->val; // 这样priority_queue才是最小堆
        }
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, complist> p_q;
        for (auto x : lists) {
            p_q.push(x);
        }

        ListNode* result = new ListNode;
        ListNode* p = result;

        while (!p_q.empty()) {
            cout << p_q.top()->val<<"\n";
            ListNode* tmp = p_q.top();
            if (tmp->next)
                p_q.push(tmp->next);
            p_q.pop();
            p->next = tmp;
            p = p->next;
        }

        return result->next;
    }
};
