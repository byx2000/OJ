// https://leetcode-cn.com/problems/find-bottom-left-tree-value/

#include "../common/common.h"

// dfs
class Solution1
{
public:
    Solution1(TreeNode* root)
        : root(root), result(0), maxDepth(0) {}

    int solve()
    {
        result = 0;
        maxDepth = -1;
        dfs(root, 0);
        return result;
    }
private:
    TreeNode* root;
    int result;
    int maxDepth;

    void dfs(TreeNode* p, int depth)
    {
        if (p == NULL) return;
        if (depth > maxDepth)
        {
            result = p->val;
            maxDepth = depth;
        }
        dfs(p->left, depth + 1);
        dfs(p->right, depth + 1);
    }
};

// bfs
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        queue<State> q;
        q.push(State(root, 0));
        int maxDepth = -1;
        int result = 0;

        while (!q.empty())
        {
            State cur = q.front();
            q.pop();

            if (cur.depth > maxDepth)
            {
                result = cur.p->val;
                maxDepth = cur.depth;
            }

            if (cur.p->left != NULL) q.push(State(cur.p->left, cur.depth + 1));
            if (cur.p->right != NULL) q.push(State(cur.p->right, cur.depth + 1));
        }

        return result;
    }

private:
    TreeNode* root;

    struct State
    {
        TreeNode* p;
        int depth;
        State(TreeNode* p, int depth) : p(p), depth(depth) {}
    };
};

class Solution 
{
public:
    int findBottomLeftValue(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1}), 1},
        {BuildTree({2,1,3}), 1},
        {BuildTree({1,2,3,4,null,5,6,null,null,7}), 7},
    };

    test(&Solution::findBottomLeftValue, cases);

	return 0;
}