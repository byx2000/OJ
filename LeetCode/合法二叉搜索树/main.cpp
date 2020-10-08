// https://leetcode-cn.com/problems/legal-binary-search-tree-lcci/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    bool solve()
    {
        try
        {
            inorder(root);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

private:
    TreeNode* root;
    vector<int> nodes;

    void inorder(TreeNode* root)
    {
        if (root == NULL) return;
        inorder(root->left);
        if (nodes.size() > 0 && nodes.back() >= root->val) throw 1;
        nodes.push_back(root->val);
        inorder(root->right);
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    bool solve()
    {
        vector<int> nodes;
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
                if (nodes.size() > 0 && nodes.back() >= cur.p->val) return false;
                nodes.push_back(cur.p->val);
                callStack.pop();
                callStack.push(Frame(cur.p->right, 0));
            }
        }

        return true;
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
    bool isValidBST(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, bool> cases
    {
        {BuildTree({}), true},
        {BuildTree({1, 1}), false},
        {BuildTree({2, 1, 3}), true},
        {BuildTree({5,1,4,null,null,3,6}), false},
        {BuildTree({10,5,15,null,null,6,20}), false},
    };

    test(&Solution::isValidBST, cases);

	return 0;
}