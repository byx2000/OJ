// https://leetcode-cn.com/problems/binary-tree-right-side-view/

#include "../common/common.h"

// bfs
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    vector<int> solve()
    {
        if (root == NULL) return {};

        queue<TreeNode*> q;
        q.push(root);
        vector<int> res;

        while (!q.empty())
        {
            res.push_back(q.back()->val);
            int cnt = q.size();
            for (int i = 0; i < cnt; ++i)
            {
                TreeNode* p = q.front();
                q.pop();
                if (p->left != NULL) q.push(p->left);
                if (p->right != NULL) q.push(p->right);
            }
        }

        return res;
    }

private:
    TreeNode* root;
};

class Solution 
{
public:
    vector<int> rightSideView(TreeNode* root) 
    {
        return Solution1(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, vector<int>> cases
    {
        {BuildTree({}), {}},
        {BuildTree({1,2,3,null,5,null,4}), {1, 3, 4}},
    };

    test(&Solution::rightSideView, cases);

	return 0;
}