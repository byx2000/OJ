// https://leetcode-cn.com/problems/linked-list-cycle/

#include "../common/common.h"

// 快慢指针
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    bool solve()
    {
        ListNode* p = head;
        ListNode* q = head;
        while (p != NULL && q != NULL && q->next != NULL)
        {
            p = p->next;
            q = q->next->next;
            if (p == q) return true;
        }
        return false;
    }

private:
    ListNode* head;
};

// 哈希表
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    bool solve()
    {
        unordered_set<ListNode*> visited;
        ListNode* p = head;
        while (p != NULL)
        {
            if (visited.count(p) > 0) return true;
            visited.insert(p);
            p = p->next;
        }
        return false;
    }

private:
    ListNode* head;
};

class Solution 
{
public:
    bool hasCycle(ListNode* head) 
    {
        //return Solution1(head).solve();
        return Solution2(head).solve();
    }
};

int main()
{
    // 无测试

	return 0;
}