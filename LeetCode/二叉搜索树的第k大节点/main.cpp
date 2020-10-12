// https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root, int k)
        : root(root), k(k), cnt(0), res(0) {}

    int solve()
    {
        cnt = 0;
        try
        {
            search(root);
        }
        catch (...)
        {
            return res;
        }
        return 0;
    }

private:
    TreeNode* root;
    int k;
    int cnt;
    int res;

    void search(TreeNode* root)
    {
        if (root == NULL) return;
        search(root->right);
        cnt++;
        if (cnt == k) { res = root->val; throw 1; }
        search(root->left);
    }
};

class Solution 
{
public:
    int kthLargest(TreeNode* root, int k) 
    {
        return Solution1(root, k).solve();
    }
};

int main()
{
    Cases<TreeNode*, int, int> cases
    {
        {BuildTree({3,1,4,null,2}), 1, 4},
        {BuildTree({5,3,6,2,4,null,null,1}), 3, 4},
    };

    test(&Solution::kthLargest, cases);

	return 0;
}