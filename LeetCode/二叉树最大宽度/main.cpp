// https://leetcode-cn.com/problems/maximum-width-of-binary-tree/

#include "../common/common.h"

// ³¬Ê±
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        queue<TreeNode*> q;
        q.push(root);
        int maxWidth = -1;

        while (!q.empty())
        {
            int count = q.size();
            int left = count;
            int right = -1;
            for (int i = 0; i < count; ++i)
            {
                TreeNode* p = q.front();
                q.pop();
                if (p == NULL)
                {
                    q.push(NULL);
                    q.push(NULL);
                }
                else
                {
                    left = min(left, i);
                    right = max(right, i);
                    q.push(p->left);
                    q.push(p->right);
                }
            }

            int width = right - left + 1;
            if (width <= 0) break;
            maxWidth = max(maxWidth, width);
        }

        return maxWidth;
    }

private:
    TreeNode* root;
};

// Òç³ö
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({ root, 1 });
        unsigned long long maxWidth = 0;

        while (!q.empty())
        {
            unsigned long long width = q.back().second - q.front().second + 1;
            maxWidth = max(maxWidth, width);

            int count = q.size();
            for (int i = 0; i < count; ++i)
            {
                TreeNode* p = q.front().first;
                unsigned long long no = q.front().second;
                q.pop();
                if (p->left != NULL) q.push({ p->left, no * 2 });
                if (p->right != NULL) q.push({ p->right, no * 2 + 1 });
            }
        }

        return (int)maxWidth;
    }

private:
    TreeNode* root;
};

class Solution 
{
public:
    int widthOfBinaryTree(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1,3,2,5,3,null,9}), 4},
        {BuildTree({1,3,null,5,3}), 2},
        {BuildTree({1,3,2,5}), 2},
        {BuildTree({1,3,2,5,null,null,9,6,null,null,7}), 8},
    };

    test(&Solution::widthOfBinaryTree, cases);

	return 0;
}