// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/

#include "../common/common.h"

// �ǵݹ�
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* p = dummy;

        // ѭ����ʼʱ��p�Լ�֮ǰ�Ľڵ��δ�ظ�����
        while (p != NULL && p->next != NULL)
        {
            int val = p->next->val;
            ListNode* q = p->next->next; // qָ����һ����p->next��ͬ�Ľڵ�
            while (q != NULL)
            {
                if (q->val == val) q = q->next;
                else break;
            }

            // p->nextû���ظ�����
            if (q == p->next->next) p = p->next;
            // p->next�ظ�����
            else p->next = q;
        }

        return dummy->next;
    }

private:
    ListNode* head;
};

// �ݹ�
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
        if (p->val != p->next->val)
        {
            p->next = deleteDuplicates(p->next);
            return p;
        }
        else
        {
            ListNode* q = p->next->next;
            // Ѱ����һ��������p->val�Ľڵ�
            while (q != NULL && q->val == p->val) q = q->next;
            return deleteDuplicates(q);
        }
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
        {BuildList({1,1}), BuildList({})},
        {BuildList({1,2}), BuildList({1,2})},
        {BuildList({1,2,3,3,4,4,5}), BuildList({1,2,5})},
        {BuildList({1,1,1,2,3}), BuildList({2,3})},
        {BuildList({1,1,1,2,2}), BuildList({})},
    };

    test(&Solution::deleteDuplicates, cases, ListEqual);

    ListNode* p = BuildList({ 1,2,3,5,8 });

	return 0;
}