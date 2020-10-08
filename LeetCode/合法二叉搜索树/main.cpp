// https://leetcode-cn.com/problems/legal-binary-search-tree-lcci/

#include "../common/common.h"

// ตÝน้
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    bool solve()
    {
        try
        {
            inorder(root);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

private:
    TreeNode* root;
    vector<int> nodes;

    void inorder(TreeNode* root)
    {
        if (root == NULL) return;
        inorder(root->left);
        if (nodes.size() > 0 && nodes.back() >= root->val) throw 1;
        nodes.push_back(root->val);
        inorder(root->right);
    }
};

class Solution 
{
public:
    bool isValidBST(TreeNode* root) 
    {
        return Solution1(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, bool> cases
    {
        {BuildTree({}), true},
        {BuildTree({1, 1}), false},
        {BuildTree({2, 1, 3}), true},
        {BuildTree({5,1,4,null,null,3,6}), false},
        {BuildTree({10,5,15,null,null,6,20}), false},
    };

    test(&Solution::isValidBST, cases);

	return 0;
}