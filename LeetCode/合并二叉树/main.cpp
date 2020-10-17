// https://leetcode-cn.com/problems/merge-two-binary-trees/

#include "../common/common.h"

class Solution 
{
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
    {
        if (t1 == NULL && t2 == NULL) return NULL;
        if (t1 != NULL && t2 == NULL) return t1;
        if (t1 == NULL && t2 != NULL) return t2;
        return new TreeNode(t1->val + t2->val, mergeTrees(t1->left, t2->left), mergeTrees(t1->right, t2->right));
    }
};

int main()
{
    Cases<TreeNode*, TreeNode*, TreeNode*> cases
    {
        {BuildTree({1,3,2,5}), BuildTree({2,1,3,null,4,null,7}), BuildTree({3,4,5,5,4,null,7})},
    };

    test(&Solution::mergeTrees, cases, TreeEqual);

	return 0;
}