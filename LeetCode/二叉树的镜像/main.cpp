// https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    TreeNode* solve()
    {
        reverse(root);
        return root;
    }

private:
    TreeNode* root;

    void reverse(TreeNode* root)
    {
        if (root == NULL) return;
        reverse(root->left);
        reverse(root->right);
        swap(root->left, root->right);
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    TreeNode* solve()
    {
        stack<Frame> callStack;
        callStack.push(Frame(root, 0));

        while (!callStack.empty())
        {
            Frame& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.p == NULL) { callStack.pop(); continue; }
                callStack.push(Frame(cur.p->left, 0));
                cur.s = 1;
            }
            else if (cur.s == 1)
            {
                callStack.push(Frame(cur.p->right, 0));
                cur.s = 2;
            }
            else
            {
                swap(cur.p->left, cur.p->right);
                callStack.pop();
            }
        }

        return root;
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
    TreeNode* mirrorTree(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, TreeNode*> cases
    {
        {BuildTree({4,2,7,1,3,6,9}), BuildTree({4,7,2,9,6,3,1})},
    };

    test(&Solution::mirrorTree, cases, TreeEqual);

	return 0;
}