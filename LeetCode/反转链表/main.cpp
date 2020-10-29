// https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/

#include "../common/common.h"

// 递归
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        if (head == NULL) return NULL;
        return reverse(head);
    }

private:
    ListNode* head;

    // 返回将p反转之后的头节点
    ListNode* reverse(ListNode* p)
    {
        if (p->next == NULL) return p;
        ListNode* t = reverse(p->next);
        p->next->next = p;
        p->next = NULL;
        return t;
    }
};

// 循环
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        if (head == NULL || head->next == NULL) return head;

        ListNode* p = head;
        ListNode* q = head->next;
        
        while (q != NULL)
        {
            ListNode* t = q->next;
            q->next = p;
            p = q;
            q = t;
        }

        head->next = NULL;
        return p;
    }

private:
    ListNode* head;
};

class Solution 
{
public:
    ListNode* reverseList(ListNode* head) 
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
        {BuildList({1,2}), BuildList({2,1})},
        {BuildList({1,2,3}), BuildList({3,2,1})},
        {BuildList({1,2,3,4,5}), BuildList({5,4,3,2,1})},
    };

    test(&Solution::reverseList, cases, ListEqual);

	return 0;
}