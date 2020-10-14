// https://leetcode-cn.com/problems/binary-tree-pruning/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    TreeNode* solve()
    {
        return cut(root);
    }

private:
    TreeNode* root;

    // 判断树t中是否包含1
    bool containOne(TreeNode* t)
    {
        if (t == NULL) return false;
        return t->val == 1 || containOne(t->left) || containOne(t->right);
    }

    // 减去树t中所有不含1的子树，返回剪枝后的树
    TreeNode* cut(TreeNode* t)
    {
        if (t == NULL) return NULL;
        if (!containOne(t)) return NULL;
        t->left = cut(t->left);
        t->right = cut(t->right);
        return t;
    }
};

class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    TreeNode* solve()
    {
        return cut(root);
    }

private:
    TreeNode* root;

    // 减去树t中所有不含1的子树，返回剪枝后的树
    TreeNode* cut(TreeNode* t)
    {
        if (t == NULL) return NULL;
        t->left = cut(t->left);
        t->right = cut(t->right);
        if (t->left == NULL && t->right == NULL && t->val != 1) return NULL;
        return t;
    }
};

class Solution 
{
public:
    TreeNode* pruneTree(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, TreeNode*> cases
    {
        {BuildTree({1,null,0,0,1}), BuildTree({1,null,0,null,1})},
        {BuildTree({1,0,1,0,0,0,1}), BuildTree({1,null,1,null,1})},
        {BuildTree({1,1,0,1,1,0,1,0}), BuildTree({1,1,0,1,1,null,1})},
    };

    test(&Solution::pruneTree, cases, TreeEqual);

	return 0;
}