// https://leetcode-cn.com/problems/longest-univalue-path/

#include "../common/common.h"

// 双重dfs
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root);
    }

private:
    TreeNode* root;

    // 以节点p为起点的最长同值路径的节点数
    int maxLength(TreeNode* p, int val)
    {
        if (p == NULL) return 0;
        if (p->val != val) return 0;
        return max(maxLength(p->left, val), maxLength(p->right, val)) + 1;
    }

    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max({ maxLength(p->left, p->val) + maxLength(p->right, p->val), dfs(p->left), dfs(p->right) });
    }
};

class Solution
{
public:
    int longestUnivaluePath(TreeNode* root)
    {
        return Solution1(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({5,4,5,1,1,5}), 2},
        {BuildTree({1,4,5,4,4,5}), 2},
    };

    test(&Solution::longestUnivaluePath, cases);

	return 0;
}