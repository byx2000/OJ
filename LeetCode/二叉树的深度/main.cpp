// https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        return depth(root);
    }

private:
    TreeNode* root;

    int depth(TreeNode* root)
    {
        if (root == NULL) return 0;
        return 1 + max(depth(root->left), depth(root->right));
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        stack<Frame> callStack;
        callStack.push(Frame(root, 0));
        int retVal = 0;

        while (!callStack.empty())
        {
            Frame& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.p == NULL) 
                { 
                    retVal = 0; callStack.pop(); continue; 
                }
                cur.s = 1;
                callStack.push(Frame(cur.p->left, 0));
            }
            else if (cur.s == 1)
            {
                cur.t = retVal;
                cur.s = 2;
                callStack.push(Frame(cur.p->right, 0));
            }
            else if (cur.s == 2)
            {
                cur.t = max(cur.t, retVal) + 1;
                retVal = cur.t;
                callStack.pop();
            }
        }

        return retVal;
    }

private:
    TreeNode* root;

    struct Frame
    {
        TreeNode* p;
        int s;
        int t;
        Frame(TreeNode* p, int s) : p(p), s(s), t(0) {}
    };
};

class Solution 
{
public:
    int maxDepth(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({3,9,20,null,null,15,7}), 3},
    };

    test(&Solution::maxDepth, cases);

	return 0;
}