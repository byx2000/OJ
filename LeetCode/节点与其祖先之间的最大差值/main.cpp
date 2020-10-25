// https://leetcode-cn.com/problems/maximum-difference-between-node-and-ancestor/

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

    // 树p中的节点与val之差绝对值的最大值
    int maxDiff(TreeNode* p, int val)
    {
        if (p == NULL) return 0;
        return max({ abs(p->val - val), maxDiff(p->left, val), maxDiff(p->right, val) });
    }

    // 遍历所有节点
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max({ maxDiff(p, p->val), dfs(p->left), dfs(p->right) });
    }
};

// 一次遍历
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root).maxDiff;
    }

private:
    TreeNode* root;

    struct Info
    {
        int maxDiff, min, max;
        Info(int maxDiff, int min, int max)
            : maxDiff(maxDiff), min(min), max(max) {}
    };

    Info dfs(TreeNode* p)
    {
        if (p == NULL) return Info(0, 0, 0);
        if (p->left == NULL && p->right == NULL)
            return Info(0, p->val, p->val);

        Info left = dfs(p->left);
        Info right = dfs(p->right);

        if (p->left == NULL)
            return Info(max({ abs(p->val - right.min), abs(p->val - right.max), right.maxDiff }), min(p->val, right.min), max(p->val, right.max));
        if (p->right == NULL)
            return Info(max({ abs(p->val - left.min), abs(p->val - left.max), left.maxDiff }), min(p->val, left.min), max(p->val, left.max));

        int min = std::min({ p->val, left.min, right.min });
        int max = std::max({ p->val, left.max, right.max });
        int maxDiff = std::max({ abs(p->val - left.min), abs(p->val - left.max), abs(p->val - right.min), abs(p->val - right.max), left.maxDiff, right.maxDiff });
        return Info(maxDiff, min, max);
    }
};

class Solution 
{
public:
    int maxAncestorDiff(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({8,3,10,1,6,null,14,null,null,4,7,13}), 7},
        {BuildTree({0,null,1}), 1},
        {BuildTree({1,null,2,null,0,3}), 3},
    };

    test(&Solution::maxAncestorDiff, cases);

	return 0;
}