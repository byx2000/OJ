// https://leetcode-cn.com/problems/successor-lcci/

#include "../common/common.h"

// 中序遍历
class Solution1
{
public:
    Solution1(TreeNode* root, TreeNode* p)
        : root(root), p(p), flag(false), result(NULL) {}

    TreeNode* solve()
    {
        flag = false;
        result = NULL;
        try
        {
            search(root);
        }
        catch (...)
        {
            return result;
        }
        return NULL;
    }

private:
    TreeNode *root, *p;
    bool flag;
    TreeNode* result;

    void search(TreeNode* cur)
    {
        if (cur == NULL) return;
        search(cur->left);
        if (flag)
        {
            result = cur;
            throw 1;
        }
        if (cur == p) flag = true;
        search(cur->right);
    }
};

// 二分查找
class Solution2
{
public:
    Solution2(TreeNode* root, TreeNode* p) : root(root), p(p) {}

    TreeNode* solve()
    {
        return search(root);
    }

private:
    TreeNode* root, * p;

    // 返回cur中大于p的第一个节点
    // 若不存在，返回NULL
    TreeNode* search(TreeNode* cur)
    {
        if (cur == NULL) return NULL;
        if (p->val >= cur->val)
        {
            return search(cur->right);
        }
        else
        {
            TreeNode* t = search(cur->left);
            return (t == NULL) ? cur : t;
        }
    }
};

class Solution 
{
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) 
    {
        //return Solution1(root, p).solve();
        return Solution2(root, p).solve();
    }
};

int main()
{
    // 无测试

	return 0;
}