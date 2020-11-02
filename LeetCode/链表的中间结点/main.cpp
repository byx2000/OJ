// https://leetcode-cn.com/problems/middle-of-the-linked-list/

#include "../common/common.h"

// ¿ìÂýÖ¸Õë
class Solution 
{
public:
    ListNode* middleNode(ListNode* head) 
    {
        ListNode* p = head;
        ListNode* q = head;
        while (p != NULL && q != NULL && q->next != NULL)
        {
            p = p->next;
            q = q->next->next;
        }
        return p;
    }
};

int main()
{
    Cases<ListNode*, ListNode*> cases
    {
        {BuildList({1}), BuildList({1})},
        {BuildList({1,2}), BuildList({2})},
        {BuildList({1,2,3,4,5}), BuildList({3,4,5})},
        {BuildList({1,2,3,4,5,6}), BuildList({4,5,6})},
    };

    test(&Solution::middleNode, cases, ListEqual);

	return 0;
}