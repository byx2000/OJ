// https://leetcode-cn.com/problems/remove-duplicate-node-lcci/

#include "../common/common.h"

// ��ϣ��
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        if (head == NULL || head->next == NULL) return head;

        ListNode* p = head;
        unordered_set<int> visited{ p->val };

        // ÿ��ѭ����ʼǰ��p�Լ�p֮ǰ��Ԫ�ؾ�û���ظ�
        while (p != NULL && p->next != NULL)
        {
            int val = p->next->val;
            if (visited.count(val) > 0) p->next = p->next->next;
            else
            {
                visited.insert(p->next->val);
                p = p->next;
            }
        }

        return head;
    }

private:
    ListNode* head;
};

// ��ʹ�ö���ռ�
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    ListNode* solve()
    {
        ListNode* p = head;
        while (p != NULL)
        {
            int val = p->val;
            ListNode* q = p;
            while (q != NULL && q->next != NULL)
            {
                if (q->next->val == val) q->next = q->next->next;
                else q = q->next;
            }
            p = p->next;
        }
        return head;
    }

private:
    ListNode* head;
};

class Solution 
{
public:
    ListNode* removeDuplicateNodes(ListNode* head) 
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
        {BuildList({1,2,3,3,2,1}), BuildList({1,2,3})},
        {BuildList({1,1,1,1,2}), BuildList({1,2})},
    };

    test(&Solution::removeDuplicateNodes, cases, ListEqual);

	return 0;
}