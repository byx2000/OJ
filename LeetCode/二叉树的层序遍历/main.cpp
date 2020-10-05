// https://leetcode-cn.com/problems/binary-tree-level-order-traversal/

#include "../common/common.h"

// ·ÇµÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    vector<vector<int>> solve()
    {
        vector<vector<int>> result;
        queue<State> q;
        q.push(State(root, 0));
        int lastLevel = -1;

        while (!q.empty())
        {
            State cur = q.front();
            q.pop();

            if (cur.p == NULL) continue;

            if (cur.level != lastLevel)
            {
                result.push_back(vector<int>());
                lastLevel = cur.level;
            }
            result.back().push_back(cur.p->val);

            if (cur.p->left != NULL) q.push(State(cur.p->left, cur.level + 1));
            if (cur.p->right != NULL) q.push(State(cur.p->right, cur.level + 1));
        }

        return result;
    }

private:
    TreeNode* root;

    struct State
    {
        TreeNode* p;
        int level;
        State(TreeNode* p, int level) : p(p), level(level) {}
    };
};

// µÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    vector<vector<int>> solve()
    {
        result.clear();
        fill(root, 0);
        return result;
    }

private:
    TreeNode* root;
    vector<vector<int>> result;

    void fill(TreeNode* root, int level)
    {
        if (root == NULL) return;
        if (level >= (int)result.size()) result.push_back(vector<int>());
        result[level].push_back(root->val);
        fill(root->left, level + 1);
        fill(root->right, level + 1);
    }
};

class Solution 
{
public:
    vector<vector<int>> levelOrder(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, vector<vector<int>>> cases
    {
        {BuildTree({3,9,20,null,null,15,7}), {{3}, {9,20}, {15, 7}}},
        {NULL, {}},
    };

    test(&Solution::levelOrder, cases);

	return 0;
}