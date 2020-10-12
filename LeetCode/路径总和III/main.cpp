// https://leetcode-cn.com/problems/path-sum-iii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root, int sum)
        : root(root), sum(sum) {}

    int solve()
    {
        return dfs(root);
    }

private:
    TreeNode* root;
    int sum;

    // ����root��ͷ�ĺ�Ϊsum��·������
    int helper(TreeNode* root, int sum)
    {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == 0) return root->val == sum;
        return helper(root->left, sum - root->val) + helper(root->right, sum - root->val) + (root->val == sum);
    }

    // ��root�����к�Ϊsum��·������
    int dfs(TreeNode* root)
    {
        if (root == NULL) return 0;
        return helper(root, sum) + dfs(root->left) + dfs(root->right);
    }
};

class Solution 
{
public:
    int pathSum(TreeNode* root, int sum) 
    {
        return Solution1(root, sum).solve();
    }
};

int main()
{
    Cases<TreeNode*, int, int> cases
    {
        {BuildTree({10,5,-3,3,2,null,11,3,-2,null,1}), 8, 3},
    };

    test(&Solution::pathSum, cases);

	return 0;
}