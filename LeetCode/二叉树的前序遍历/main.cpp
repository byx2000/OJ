// https://leetcode-cn.com/problems/binary-tree-preorder-traversal/

#include "../common/common.h"

class Solution 
{
public:
    vector<int> preorderTraversal(TreeNode* root) 
    {
        return vector<int>();
    }
};

int main()
{
    Cases<TreeNode*, vector<int>> cases
    {
        {BuildTree({1,null,2,3}), {1,2,3}},
    };

    test(&Solution::preorderTraversal, cases);

	return 0;
}