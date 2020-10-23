// https://leetcode-cn.com/problems/sum-of-left-leaves/

#include "../common/common.h"

class Solution 
{
public:
    int sumOfLeftLeaves(TreeNode* root) 
    {
        sum = 0;
        search(root);
        return sum;
    }

private:
    int sum;

    void search(TreeNode* p)
    {
        if (p == NULL) return;
        if (isLeaf(p->left)) sum += p->left->val;
        search(p->left);
        search(p->right);
    }

    bool isLeaf(TreeNode* p)
    {
        return p != NULL && p->left == NULL && p->right == NULL;
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({3,9,20,null,null,15,7}), 24},
    };

    test(&Solution::sumOfLeftLeaves, cases);

	return 0;
}