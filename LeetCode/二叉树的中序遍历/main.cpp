// https://leetcode-cn.com/problems/binary-tree-inorder-traversal/

#include "../common/common.h"

// �ݹ�
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
        result.push_back(root->val);
        traverse(root->right);
    }
};

// �ǵݹ�
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
                cur.s = 1;
                callStack.push(Frame(cur.p->left, 0));
            }
            else if (cur.s == 1)
            {
                result.push_back(cur.p->val);
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
    vector<int> inorderTraversal(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, vector<int>> cases
    {
        {BuildTree({1,null,2,3}), {1,3,2}},
    };

    test(&Solution::inorderTraversal, cases);

	return 0;
}