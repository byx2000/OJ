// https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/

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

    // 从p节点开始到叶节点的路径上节点值之和最大值
    int maxSum(TreeNode* p)
    {
        if (p == NULL) return 0;
        int left = max(maxSum(p->left) + p->val, p->val);
        int right = max(maxSum(p->right) + p->val, p->val);
        return max(left, right);
    }

    // 整棵树中路径上节点值之和最大值
    int dfs(TreeNode* p) 
    {
        if (p == NULL) return numeric_limits<int>::min();
        int left = maxSum(p->left);
        int right = maxSum(p->right);
        int sum = p->val;
        if (left > 0) sum += left;
        if (right > 0) sum += right;
        return max({ sum, dfs(p->left), dfs(p->right) });
    }
};

// 一次遍历
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root).second;
    }

private:
    TreeNode* root;

    // 返回 { 以p为起点到叶节点的路径上节点值之和最大值, 整棵树中路径上节点值之和最大值 }
    pair<int, int> dfs(TreeNode* p)
    {
        if (p == NULL) return { 0, numeric_limits<int>::min() };
        pair<int, int> left = dfs(p->left);
        pair<int, int> right = dfs(p->right);
        int r1 = max(max(left.first + p->val, p->val), max(right.first + p->val, p->val));
        int sum = p->val;
        if (left.first > 0) sum += left.first;
        if (right.first > 0) sum += right.first;
        int r2 = max({ sum, left.second, right.second });
        return { r1, r2 };
    }
};

class Solution 
{
public:
    int maxPathSum(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1,2,3}), 6},
        {BuildTree({-10,9,20,null,null,15,7}), 42},
    };

    test(&Solution::maxPathSum, cases);

	return 0;
}