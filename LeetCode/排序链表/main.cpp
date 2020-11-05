// https://leetcode-cn.com/problems/sort-list/

#include "../common/common.h"

// 归并排序
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        return sort(head);
    }

private:
    ListNode* head;

    // 合并两个有序链表
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

    // 找到链表的中点
    ListNode* middle(ListNode* p)
    {
        if (p == NULL) return NULL;
        ListNode* q = p;
        while (p != NULL && q != NULL && q->next != NULL && q->next->next != NULL)
        {
            p = p->next;
            q = q->next->next;
        }
        return p;
    }

    // 归并排序
    ListNode* sort(ListNode* p)
    {
        if (p == NULL || p->next == NULL) return p;
        ListNode* m = middle(p);
        ListNode* q = m->next;
        m->next = NULL;
        p = sort(p);
        q = sort(q);
        return merge(p, q);
    }
};

// 选择排序
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        if (head == NULL || head->next == NULL) return head;

        for (ListNode* p = head; p != NULL; p = p->next)
        {
            for (ListNode* q = p->next; q != NULL; q = q->next)
            {
                if (p->val > q->val) swap(p->val, q->val);
            }
        }

        return head;
    }

private:
    ListNode* head;
};

class Solution
{
public:
    ListNode* sortList(ListNode* head) 
    {
        //return Solution1(head).solve();
        return Solution2(head).solve();
    }
};

int main()
{
    Cases<ListNode*, ListNode*> cases
    {
        {BuildList({}), BuildList({})},
        {BuildList({1}), BuildList({1})},
        {BuildList({1,2}), BuildList({1,2})},
        {BuildList({2,1}), BuildList({1,2})},
        {BuildList({4,2,1,3}), BuildList({1,2,3,4})},
        {BuildList({-1,5,3,4,0}), BuildList({-1,0,3,4,5})},
    };

    test(&Solution::sortList, cases, ListEqual);

	return 0;
}