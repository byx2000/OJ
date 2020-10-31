// https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(ListNode* p, ListNode* q)
        : p(p), q(q) {}

    ListNode* solve()
    {
        return merge(p, q);
    }

private:
    ListNode *p, *q;

    ListNode* merge(ListNode* p, ListNode* q)
    {
        if (p == NULL) return q;
        if (q == NULL) return p;
        if (p->val < q->val)
        {
            p->next = merge(p->next, q);
            return p;
        }
        else
        {
            q->next = merge(p, q->next);
            return q;
        }
    }
};

// Ñ­»·
class Solution2
{
public:
    Solution2(ListNode* p, ListNode* q)
        : p(p), q(q) {}

    ListNode* solve()
    {
        ListNode* dummy = new ListNode(0);
        ListNode* r = dummy;
        while (p != NULL && q != NULL)
        {
            if (p->val < q->val)
            {
                r->next = p;
                p = p->next;
            }
            else
            {
                r->next = q;
                q = q->next;
            }
            r = r->next;
        }

        if (p != NULL) r->next = p;
        if (q != NULL) r->next = q;

        return dummy->next;
    }

private:
    ListNode *p, *q;
};

class Solution 
{
public:
    ListNode* mergeTwoLists(ListNode* p, ListNode* q) 
    {
        //return Solution1(p, q).solve();
        return Solution2(p, q).solve();
    }
};

int main()
{
    Cases<ListNode*, ListNode*, ListNode*> cases
    {
        {BuildList({1,2,4}), BuildList({1,3,4}), BuildList({1,1,2,3,4,4})},
    };

    test(&Solution::mergeTwoLists, cases, ListEqual);

	return 0;
}