// https://leetcode-cn.com/problems/binary-tree-preorder-traversal/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    vector<int> solve()
    {
        result.clear();
        traverse(root);
        return result;
    }

private:
    TreeNode* root;
    vector<int> result;

    void traverse(TreeNode* root)
    {
        if (root == NULL) return;
        result.push_back(root->val);
        traverse(root->left);
        traverse(root->right);
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    vector<int> solve()
    {
        vector<int> result;
        stack<Frame> callStack;
        callStack.push(Frame(root, 0));

        while (!callStack.empty())
        {
            Frame& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.p == NULL) { callStack.pop(); continue; }
                result.push_back(cur.p->val);
                cur.s = 1;
                callStack.push(Frame(cur.p->left, 0));
            }
            else if (cur.s == 1)
            {
                cur.s = 2;
                callStack.push(Frame(cur.p->right, 0));
            }
            else
            {
                callStack.pop();
            }
        }

        return result;
    }

private:
    TreeNode* root;

    struct Frame
    {
        TreeNode* p;
        int s;
        Frame(TreeNode* p, int s) : p(p), s(s) {}
    };
};

class Solution 
{
public:
    vector<int> preorderTraversal(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, vector<int>> cases
    {
        {BuildTree({1,null,2,3}), {1,2,3}},
    };

    test(&Solution::preorderTraversal, cases);

	return 0;
}