// https://leetcode-cn.com/problems/kth-node-from-end-of-list-lcci/

#include "../common/common.h"

// ¿ìÂýÖ¸Õë
class Solution1
{
public:
    Solution1(ListNode* head, int k)
        : head(head), k(k) {}

    int solve()
    {
        ListNode* p = head;
        for (int i = 0; i < k; ++i) p = p->next;
        ListNode* q = head;
        while (p != NULL)
        {
            p = p->next;
            q = q->next;
        }
        return q->val;
    }

private:
    ListNode* head;
    int k;
};

// µÝ¹é
class Solution2
{
public:
    Solution2(ListNode* head, int k)
        : head(head), k(k), cnt(0), result(0) {}

    int solve()
    {
        cnt = 0;
        search(head);
        return result;
    }

private:
    ListNode* head;
    int k;
    int cnt;
    int result;

    void search(ListNode* p)
    {
        if (p == NULL) return;
        search(p->next);
        cnt++;
        if (cnt == k) result = p->val;
    }
};

class Solution 
{
public:
    int kthToLast(ListNode* head, int k) 
    {
        //return Solution1(head, k).solve();
        return Solution2(head, k).solve();
    }
};

int main()
{
    Cases<ListNode*, int, int> cases
    {
        {BuildList({1,2,3,4,5}), 2, 4},
    };

    test(&Solution::kthToLast, cases);

	return 0;
}