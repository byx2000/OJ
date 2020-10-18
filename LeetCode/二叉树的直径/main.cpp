// https://leetcode-cn.com/problems/diameter-of-binary-tree/

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

    // p的高度
    int height(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max(height(p->left), height(p->right)) + 1;
    }

    // p中的最长路径
    // 等价于求p中所有子树的左右子树高度之和最大值
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max({ height(p->left) + height(p->right), dfs(p->left), dfs(p->right) });
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

    // 返回 { p的高度, p中所有子树的左右子树高度之和最大值 }
    pair<int, int> dfs(TreeNode* p)
    {
        if (p == NULL) return { 0, 0 };
        pair<int, int> left = dfs(p->left);
        pair<int, int> right = dfs(p->right);
        return { max(left.first, right.first) + 1, max({left.first + right.first, left.second, right.second}) };
    }
};

class Solution 
{
public:
    int diameterOfBinaryTree(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({ 1,2,3,4,5 }), 3},
    };

    test(&Solution::diameterOfBinaryTree, cases);

	return 0;
}