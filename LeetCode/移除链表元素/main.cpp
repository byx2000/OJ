// https://leetcode-cn.com/problems/remove-linked-list-elements/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(ListNode* head, int val)
        : head(head), val(val) {}

    ListNode* solve()
    {
        return remove(head);
    }

private:
    ListNode* head;
    int val;

    ListNode* remove(ListNode* p)
    {
        if (p == NULL) return NULL;
        if (p->val == val) return remove(p->next);
        p->next = remove(p->next);
        return p;
    }
};

// Ñ­»·
class Solution2
{
public:
    Solution2(ListNode* head, int val)
        : head(head), val(val) {}

    ListNode* solve()
    {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* p = dummy;

        while (p != NULL && p->next != NULL)
        {
            if (p->next->val == val)
                p->next = p->next->next;
            else 
                p = p->next;
        }

        return dummy->next;
    }

private:
    ListNode* head;
    int val;
};

class Solution 
{
public:
    ListNode* removeElements(ListNode* head, int val) 
    {
        //return Solution1(head, val).solve();
        return Solution2(head, val).solve();
    }
};

int main()
{
    Cases<ListNode*, int, ListNode*> cases
    {
        {BuildList({1,2,6,3,4,5,6}), 6, BuildList({1,2,3,4,5})},
        {BuildList({1,2,3,6,6}), 6, BuildList({1,2,3})},
    };

    test(&Solution::removeElements, cases, ListEqual);

	return 0;
}