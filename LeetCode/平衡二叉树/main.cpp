// https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/

#include "../common/common.h"

// 递归1
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    bool solve()
    {
        return isBalanced(root);
    }

private:
    TreeNode* root;

    int depth(TreeNode* root)
    {
        if (root == NULL) return 0;
        return 1 + max(depth(root->left), depth(root->right));
    }

    bool isBalanced(TreeNode* root)
    {
        if (root == NULL) return true;
        return isBalanced(root->left) && 
               isBalanced(root->right) && 
               abs(depth(root->left) - depth(root->right)) <= 1;
    }
};

// 递归2
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        return search(root) != -1;
    }

private:
    TreeNode* root;

    // 如果root是平衡二叉树，返回root的深度，否则返回-1
    int search(TreeNode* root)
    {
        if (root == NULL) return 0;

        int left = search(root->left);
        if (left == -1) return -1;

        int right = search(root->right);
        if (right == -1) return -1;

        if (abs(left - right) <= 1) return 1 + max(left, right);
        else return -1;
    }
};

class Solution 
{
public:
    bool isBalanced(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, bool> cases
    {
        {BuildTree({null}), true},
        {BuildTree({1}), true},
        {BuildTree({1, 2}), true},
        {BuildTree({1, 2, 3}), true},
        {BuildTree({3,9,20,null,null,15,7}), true},
        {BuildTree({1,2,2,3,3,null,null,4,4}), false},
        {BuildTree({1,2,2,3,null,null,3,4,null,null,4}), false},
    };

    test(&Solution::isBalanced, cases);

	return 0;
}