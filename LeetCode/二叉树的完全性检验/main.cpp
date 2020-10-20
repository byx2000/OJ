// https://leetcode-cn.com/problems/check-completeness-of-a-binary-tree/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    bool solve()
    {
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 1));
        int count = 0;
        int lastId = 0;

        while (!q.empty())
        {
            TreeNode* p = q.front().first;
            lastId = q.front().second;
            q.pop();
            count++;
            if (lastId != count) return false;
            if (p->left != NULL) q.push(make_pair(p->left, lastId * 2));
            if (p->right != NULL) q.push(make_pair(p->right, lastId * 2 + 1));
            
        }

        return count == lastId;
    }

private:
    TreeNode* root;
};

class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    bool solve()
    {
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode* p = q.front();
            q.pop();
            if (p == NULL) break;
            q.push(p->left);
            q.push(p->right);
        }

        while (!q.empty())
        {
            if (q.front() != NULL) return false;
            q.pop();
        }

        return true;
    }

private:
    TreeNode* root;
};

class Solution 
{
public:
    bool isCompleteTree(TreeNode* root)
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, bool> cases
    {
        {BuildTree({1,2,3,4,5,6}), true},
        {BuildTree({1,2,3,4,5,null,7}), false},
        {BuildTree({1,null,2,null,3,null,4,null,5}), false},
    };

    test(&Solution::isCompleteTree, cases);

	return 0;
}