// https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root, TreeNode* p, TreeNode* q)
        : root(root), p(p), q(q) {}

    TreeNode* solve()
    {
        vector<TreeNode*> p1 = findPath(root, p);
        vector<TreeNode*> p2 = findPath(root, q);

        for (auto i = p1.begin(); i != p1.end(); ++i)
        {
            if (find(p2.begin(), p2.end(), *i) != p2.end())
            {
                return *i;
            }
        }
        return NULL;
    }

private:
    TreeNode* root, * p, * q;

    // 返回从start到target的路径（倒序）
    vector<TreeNode*> findPath(TreeNode* start, TreeNode* target)
    {
        if (start == NULL) return {};
        if (start == target) return { start };
        vector<TreeNode*> left = findPath(start->left, target);
        vector<TreeNode*> right = findPath(start->right, target);
        if (!left.empty()) { left.push_back(start); return left; }
        else if (!right.empty()) { right.push_back(start); return right; }
        else return {};
    }
};

class Solution2
{
public:
    Solution2(TreeNode* root, TreeNode* p, TreeNode* q)
        : root(root), p(p), q(q) {}

    TreeNode* solve()
    {
        return LCA(root, p, q);
    }

private:
    TreeNode *root, *p, *q;

    TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == NULL) return NULL;
        if (root == p || root == q) return root;
        TreeNode* left = LCA(root->left, p, q);
        TreeNode* right = LCA(root->right, p, q);
        if (left != NULL && right != NULL) return root;
        return (left != NULL) ? left : right;
    }
};

class Solution 
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        //return Solution1(root, p, q).solve();
        return Solution2(root, p, q).solve();
    }
};

int main()
{
    // 无测试

	return 0;
}