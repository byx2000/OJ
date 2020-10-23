// https://leetcode-cn.com/problems/deepest-leaves-sum/

#include "../common/common.h"

// bfs 1
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        queue<pair<TreeNode*, int>> q;
        q.push({ root, 1 });
        int maxDepth = -1;
        int sum = 0;

        while (!q.empty())
        {
            TreeNode* p = q.front().first;
            int depth = q.front().second;
            q.pop();

            if (p->left == NULL && p->right == NULL)
            {
                if (depth > maxDepth) // 出现更深的叶子节点
                {
                    maxDepth = depth;
                    sum = 0;
                }
                sum += p->val;
            }

            if (p->left != NULL) q.push({ p->left, depth + 1 });
            if (p->right != NULL) q.push({ p->right, depth + 1 });
        }

        return sum;
    }

private:
    TreeNode* root;
};

// bfs 2
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        queue<TreeNode*> q;
        q.push(root);
        int sum = 0;

        while (!q.empty())
        {
            // 此时q中保存着上一层的所有节点
            // 计算上一层节点之和，并扩展下一层节点
            sum = 0;
            int count = q.size();
            for (int i = 0; i < count; ++i)
            {
                TreeNode* p = q.front();
                q.pop();
                sum += p->val;
                if (p->left != NULL) q.push(p->left);
                if (p->right != NULL) q.push(p->right);
            }
        }

        return sum;
    }

private:
    TreeNode* root;
};

// dfs
class Solution3
{
public:
    Solution3(TreeNode* root)
        : root(root), maxDepth(0), sum(0) {}

    int solve()
    {
        maxDepth = 0;
        sum = 0;
        dfs(root, 1);
        return sum;
    }

private:
    TreeNode* root;
    int maxDepth;
    int sum;

    void dfs(TreeNode* p, int depth)
    {
        if (p == NULL) return;

        if (depth > maxDepth)
        {
            maxDepth = depth;
            sum = p->val;
        }
        else if (depth == maxDepth)
        {
            sum += p->val;
        }

        dfs(p->left, depth + 1);
        dfs(p->right, depth + 1);
    }
};

class Solution 
{
public:
    int deepestLeavesSum(TreeNode* root) 
    {
        //return Solution1(root).solve();
        //return Solution2(root).solve();
        return Solution3(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1,2,3,4,5,null,6,7,null,null,null,null,8}), 15},
    };

    test(&Solution::deepestLeavesSum, cases);

	return 0;
}