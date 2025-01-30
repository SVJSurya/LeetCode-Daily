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
    ListNode* reverseList(ListNode* h) {
        ListNode* temp = NULL;
        while (h != NULL) {
            ListNode* temp1 = h->next;
            h->next = temp;
            temp  = h;
            h = temp1;
        }
        return temp;
    }
};