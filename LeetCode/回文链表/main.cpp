// https://leetcode-cn.com/problems/palindrome-linked-list-lcci/

#include "../common/common.h"

// ·ÇµÝ¹é
class Solution1
{
public:
    Solution1(ListNode* head) : head(head) {}

    bool solve()
    {
        stack<int> s;
        ListNode* p = head;
        while (p != NULL)
        {
            s.push(p->val);
            p = p->next;
        }

        p = head;
        while (p != NULL)
        {
            if (p->val != s.top()) return false;
            p = p->next;
            s.pop();
        }

        return true;
    }

private:
    ListNode* head;
};

// µÝ¹é
class Solution2
{
public:
    Solution2(ListNode* head) : head(head) {}

    bool solve()
    {
        try
        {
            search(head);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

private:
    ListNode* head;

    void search(ListNode* p)
    {
        if (p == NULL) return;
        search(p->next);
        if (head->val != p->val) throw 1;
        head = head->next;
    }
};

class Solution 
{
public:
    bool isPalindrome(ListNode* head) 
    {
        //return Solution1(head).solve();
        return Solution2(head).solve();
    }
};

int main()
{
    Cases<ListNode*, bool> cases
    {
        {BuildList({1}), true},
        {BuildList({1,2,1}), true},
        {BuildList({1,2,2,1}), true},
        {BuildList({1,2}), false},
        {BuildList({1,2,3}), false},
    };

    test(&Solution::isPalindrome, cases);

	return 0;
}