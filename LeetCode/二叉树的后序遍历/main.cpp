// https://leetcode-cn.com/problems/binary-tree-postorder-traversal/

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
        traverse(root->left);
        traverse(root->right);
        result.push_back(root->val);
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
        stack<State> callStack;
        callStack.push(State(root, 0));

        while (!callStack.empty())
        {
            State& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.p == NULL) { callStack.pop(); continue; }
                cur.s = 1;
                callStack.push(State(cur.p->left, 0));
            }
            else if (cur.s == 1)
            {
                cur.s = 2;
                callStack.push(State(cur.p->right, 0));
            }
            else
            {
                result.push_back(cur.p->val);
                callStack.pop();
            }
        }

        return result;
    }

private:
    TreeNode* root;

    struct State
    {
        TreeNode* p;
        int s;
        State(TreeNode* p, int s) : p(p), s(s) {}
    };
};

class Solution
{
public:
    vector<int> postorderTraversal(TreeNode* root)
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, vector<int>> cases
    {
        {BuildTree({1,null,2,3}), {3,2,1}},
    };

    test(&Solution::postorderTraversal, cases);

    return 0;
}