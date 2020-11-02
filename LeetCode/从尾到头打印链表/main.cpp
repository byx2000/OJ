// https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/

#include "../common/common.h"

class Solution 
{
public:
    vector<int> reversePrint(ListNode* head)
    {
        result.clear();
        reverse(head);
        return result;
    }

private:
    vector<int> result;

    void reverse(ListNode* p)
    {
        if (p == NULL) return;
        reverse(p->next);
        result.push_back(p->val);
    }
};

int main()
{
    Cases<ListNode*, vector<int>> cases
    {
        {BuildList({1,3,2}), {{2,3,1}}},
    };

    test(&Solution::reversePrint, cases);

	return 0;
}