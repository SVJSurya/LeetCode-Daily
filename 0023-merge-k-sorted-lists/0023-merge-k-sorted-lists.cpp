/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*,vector<ListNode*> ,decltype(compare) > pq(compare);
        for(ListNode* list: lists) {
            if(list != nullptr) {
                pq.push(list);
            }
        }
        ListNode* h = new ListNode(0);
        ListNode* cur = h;
        while(!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            cur->next = node;
            cur = cur->next;
            if(node->next != nullptr) {
                pq.push(node->next);
            }
        } 
        return h->next;
    }
};