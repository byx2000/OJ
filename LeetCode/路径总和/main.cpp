// https://leetcode-cn.com/problems/path-sum/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root, int sum) : root(root), sum(sum) {}

    bool solve()
    {
        return hasPathSum(root, sum);
    }

private:
    TreeNode* root;
    int sum;

    bool hasPathSum(TreeNode* root, int sum)
    {
        if (root == NULL) return false;
        if (root->left == NULL && root->right == NULL) return sum == root->val;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root, int sum) : root(root), sum(sum) {}

    bool solve()
    {
        bool retVal = false;
        stack<State> callStack;
        callStack.push(State(root, sum, 0));

        while (!callStack.empty())
        {
            State& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.p == NULL) 
                { 
                    retVal = false; 
                    callStack.pop();
                    continue; 
                }
                else if (cur.p->left == NULL && cur.p->right == NULL) 
                { 
                    retVal = cur.p->val == cur.sum;
                    callStack.pop(); 
                    continue;
                }

                cur.s = 1;
                callStack.push(State(cur.p->left, cur.sum - cur.p->val, 0));
            }
            else if (cur.s == 1)
            {
                cur.t = retVal;
                cur.s = 2;
                callStack.push(State(cur.p->right, cur.sum - cur.p->val, 0));
            }
            else
            {
                cur.t = cur.t || retVal;
                retVal = cur.t;
                callStack.pop();
            }
        }

        return retVal;
    }

private:
    TreeNode* root;
    int sum;

    struct State
    {
        TreeNode* p;
        int sum;
        int s;
        bool t;
        State(TreeNode* p, int sum, int s) : p(p), sum(sum), s(s), t(false) {}
    };
};

class Solution 
{
public:
    bool hasPathSum(TreeNode* root, int sum) 
    {
        //return Solution1(root, sum).solve();
        return Solution2(root, sum).solve();
    }
};

int main()
{
    Cases<TreeNode*, int, bool> cases
    {
        {BuildTree({}), 0, false},
        {BuildTree({1, 2}), 1, false},
        {BuildTree({5,4,8,11,null,13,4,7,2,null,null,null,1}), 22, true},
    };

    test(&Solution::hasPathSum, cases);

	return 0;
}