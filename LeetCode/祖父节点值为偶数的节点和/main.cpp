// https://leetcode-cn.com/problems/sum-of-nodes-with-even-valued-grandparent/

#include "../common/common.h"

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

    // 求节点p的所有孙节点的和
    int sumOfGrandson(TreeNode* p)
    {
        if (p == NULL) return 0;
        vector<TreeNode*> v{ p->left, p->right };
        int sum = 0;
        for (TreeNode* t : v)
        {
            if (t != NULL)
            {
                if (t->left != NULL) sum += t->left->val;
                if (t->right != NULL) sum += t->right->val;
            }
        }
        return sum;
    }

    // 遍历所有节点
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        if (p->val % 2 == 0) return sumOfGrandson(p) + dfs(p->left) + dfs(p->right);
        else return dfs(p->left) + dfs(p->right);
    }
};

class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root, -1, -1);
    }

private:
    TreeNode* root;

    int dfs(TreeNode* p, int parent, int grandparent)
    {
        if (p == NULL) return 0;

        int ret = 0;
        if (grandparent % 2 == 0) ret += p->val;
        ret += dfs(p->left, p->val, parent);
        ret += dfs(p->right, p->val, parent);

        return ret;
    }
};

class Solution 
{
public:
    int sumEvenGrandparent(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({6,7,8,2,7,1,3,9,null,1,4,null,null,null,5}), 18},
    };

    test(&Solution::sumEvenGrandparent, cases);

	return 0;
}