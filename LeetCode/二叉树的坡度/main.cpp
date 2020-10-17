// https://leetcode-cn.com/problems/binary-tree-tilt/

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

    // 遍历所有节点
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return abs(sum(p->left) - sum(p->right)) + dfs(p->left) + dfs(p->right);
    }

    // 求子树p的所有节点之和
    int sum(TreeNode* p)
    {
        if (p == NULL) return 0;
        return p->val + sum(p->left) + sum(p->right);
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

    // 返回 { 子树p的和, 子树p的坡度 }
    pair<int, int> dfs(TreeNode* p)
    {
        if (p == NULL) return { 0, 0 };
        pair<int, int> left = dfs(p->left);
        pair<int, int> right = dfs(p->right);
        return { p->val + left.first + right.first, abs(left.first - right.first) + left.second + right.second };
    }
};

class Solution 
{
public:
    int findTilt(TreeNode* root)
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1,2,3}), 1},
        {BuildTree({1,2,3,4,null,5}), 11},
    };

    test(&Solution::findTilt, cases);

	return 0;
}