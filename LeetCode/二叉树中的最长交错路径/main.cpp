// https://leetcode-cn.com/problems/longest-zigzag-path-in-a-binary-tree/

#include "../common/common.h"

// 动态规划
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        cache.clear();
        return dfs(root);
    }

private:
    TreeNode* root;
    map<pair<TreeNode*, bool>, int> cache;

    // 以节点p为开头的最长交错路径
    // 假设p != NULL
    // direction == true表示第一段向左偏
    int maxLen(TreeNode* p, bool direction)
    {
        pair<TreeNode*, bool> key(p, direction);
        if (cache.count(key) > 0) return cache[key];
        if (p->left == NULL && p->right == NULL) return cache[key] = 0;
        if (direction) return cache[key] = (p->left != NULL) ? 1 + maxLen(p->left, !direction) : 0;
        else return cache[key] = (p->right != NULL) ? 1 + maxLen(p->right, !direction) : 0;
    }

    // 遍历所有节点
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max({ maxLen(p, true), maxLen(p, false), dfs(p->left), dfs(p->right) });
    }
};

class Solution 
{
public:
    int longestZigZag(TreeNode* root) 
    {
        return Solution1(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1}), 0},
        {BuildTree({1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1}), 3},
        {BuildTree({1,1,1,null,1,null,null,1,1,null,1}), 4},
    };

    test(&Solution::longestZigZag, cases);

	return 0;
}