// https://leetcode-cn.com/problems/delete-leaves-with-a-given-value/

#include "../common/common.h"

// µÝ¹é
class Solution1
{
public:
    Solution1(TreeNode* root, int target) : root(root), target(target) {}

    TreeNode* solve()
    {
        return remove(root, target);
    }

private:
    TreeNode* root;
    int target;

    TreeNode* remove(TreeNode* root, int target)
    {
        if (root == NULL) return NULL;
        root->left = remove(root->left, target);
        root->right = remove(root->right, target);
        if (root->left == NULL && root->right == NULL && root->val == target) return NULL;
        return root;
    }
};

// ·ÇµÝ¹é
class Solution2
{
public:
    Solution2(TreeNode* root, int target) : root(root), target(target) {}

    TreeNode* solve()
    {
        TreeNode* retVal = NULL;

        stack<Frame> callStack;
        callStack.push(Frame(root, target));

        while (!callStack.empty())
        {
            Frame& cur = callStack.top();
            
            if (cur.s == 0)
            {
                if (cur.root == NULL) 
                { 
                    retVal = NULL;
                    callStack.pop(); 
                    continue; 
                }
                callStack.push(Frame(cur.root->left, cur.target));
                cur.s = 1;
            }
            else if (cur.s == 1)
            {
                cur.root->left = retVal;
                callStack.push(Frame(cur.root->right, cur.target));
                cur.s = 2;
            }
            else if (cur.s == 2)
            {
                cur.root->right = retVal;
                if (cur.root->left == NULL && cur.root->right == NULL && cur.root->val == cur.target)
                {
                    retVal = NULL;
                    callStack.pop();
                    continue;
                }
                retVal = cur.root;
                callStack.pop();
                continue;
            }
        }

        return retVal;
    }

private:
    TreeNode* root;
    int target;

    struct Frame
    {
        TreeNode* root;
        int target;
        int s;
        Frame(TreeNode* root, int target) : root(root), target(target), s(0) {}
    };
};

class Solution 
{
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        //return Solution1(root, target).solve();
        return Solution2(root, target).solve();
    }
};

int main()
{
    Cases<TreeNode*, int, TreeNode*> cases
    {
        {BuildTree({1,2,3,2,null,2,4}), 2, BuildTree({1,null,3,null,4})},
    };

    test(&Solution::removeLeafNodes, cases, TreeEqual);

	return 0;
}