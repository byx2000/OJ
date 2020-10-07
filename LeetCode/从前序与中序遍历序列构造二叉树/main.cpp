// https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& pre, const vector<int>& in)
        : pre(pre), in(in) {}

    TreeNode* solve()
    {
        return build(0, pre.size() - 1, 0, in.size() - 1);
    }

private:
    vector<int> pre, in;

    // 前序遍历为pre[b1]~pre[e1]， 后序遍历为in[b2]~in[e2]
    TreeNode* build(int b1, int e1, int b2, int e2)
    {
        if (b1 > e1) return NULL;
        
        // 构造根节点
        int val = pre[b1];
        TreeNode* p = new TreeNode(val);

        if (b1 == e1) return p;

        // 计算根节点在中序遍历中的索引
        vector<int>::iterator it = find(in.begin() + b2, in.begin() + e2 + 1, val);
        int index = distance(in.begin(), it);

        // 计算左右子树的节点数
        int len1 = index - b2;
        int len2 = e2 - index;

        // 递归构造左右子树
        p->left = build(b1 + 1, b1 + len1, b2, index - 1);
        p->right = build(b1 + len1 + 1, e1, index + 1, e2);

        return p;
    }
};

class Solution 
{
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        return Solution1(preorder, inorder).solve();
    }
};

int main()
{
    Cases<vector<int>, vector<int>, TreeNode*> cases
    {
        {{}, {}, BuildTree({})},
        {{3,9,20,15,7}, {9,3,15,20,7}, BuildTree({3,9,20,null,null,15,7})},
    };

    test(&Solution::buildTree, cases, TreeEqual);

	return 0;
}