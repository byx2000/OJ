// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/

#include "../common/common.h"

// ·ÇµÝ¹é
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        ListNode* p = head;
        while (p != NULL)
        {
            ListNode* q = p->next;
            while (q != NULL)
            {
                if (q->val == p->val) q = q->next;
                else break;
            }
            p->next = q;
            p = p->next;
        }
        return head;
    }

private:
    ListNode* head;
};

// µÝ¹é
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        return deleteDuplicates(head);
    }

private:
    ListNode* head;

    ListNode* deleteDuplicates(ListNode* p)
    {
        if (p == NULL || p->next == NULL) return p;
        if (p->val == p->next->val) return deleteDuplicates(p->next);
        p->next = deleteDuplicates(p->next);
        return p;
    }
};

class Solution 
{
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        //return Solution1(head).solve();
        return Solution2(head).solve();
    }
};

int main()
{
    Cases<ListNode*, ListNode*> cases
    {
        {BuildList({1}), BuildList({1})},
        {BuildList({1,1}), BuildList({1})},
        {BuildList({1,2}), BuildList({1,2})},
        {BuildList({1,1,2}), BuildList({1,2})},
        {BuildList({1,1,2,3,3}), BuildList({1,2,3})},
    };

    test(&Solution::deleteDuplicates, cases, ListEqual);

	return 0;
}