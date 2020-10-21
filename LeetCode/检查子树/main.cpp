// https://www.bilibili.com/video/BV1N54y1i7dG?p=6

#include "../common/common.h"

// 双重dfs
class Solution1
{
public:
    Solution1(TreeNode* t1, TreeNode* t2)
        : t1(t1), t2(t2) {}

    bool solve()
    {
        return isSub(t1, t2);
    }

private:
    TreeNode *t1, *t2;

    // 判断两棵树是否相等
    bool same(TreeNode* p1, TreeNode* p2)
    {
        if (p1 == NULL || p2 == NULL) return p1 == p2;
        return p1->val == p2->val && same(p1->left, p2->left) && same(p2->left, p2->left);
    }

    // 判断p2是否是p1的子树
    bool isSub(TreeNode* p1, TreeNode* p2)
    {
        if (p1 == NULL) return false;
        return same(p1, p2) || isSub(p1->left, p2) || isSub(p1->right, p2);
    }
};

class Solution 
{
public:
    bool checkSubTree(TreeNode* t1, TreeNode* t2) 
    {
        return Solution1(t1, t2).solve();
    }
};

int main()
{
    Cases <TreeNode*, TreeNode*, bool> cases
    {
        {BuildTree({1, 2, 3}), BuildTree({2}), true},
        {BuildTree({1, null, 2, 4}), BuildTree({3, 2}), false},
    };

    test(&Solution::checkSubTree, cases);

	return 0;
}