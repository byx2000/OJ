// https://leetcode-cn.com/problems/delete-middle-node-lcci/

#include "../common/common.h"

class Solution 
{
public:
    void deleteNode(ListNode* node)
    {
        *node = *(node->next);
    }
};

int main()
{
	// �޲���

	return 0;
}