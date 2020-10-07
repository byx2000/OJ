// https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& in, const vector<int>& post)
        : in(in), post(post) {}

    TreeNode* solve()
    {
        return build(0, post.size() - 1, 0, in.size() - 1);
    }

private:
    vector<int> in, post;

    // 后序遍历为post[b1]~post[e1]， 中序遍历为in[b2]~in[e2]
    TreeNode* build(int b1, int e1, int b2, int e2)
    {
        if (b1 > e1) return NULL;

        // 构造根节点
        int val = post[e1];
        TreeNode* p = new TreeNode(val);

        if (b1 == e1) return p;

        // 计算根节点在中序遍历中的索引
        vector<int>::iterator it = find(in.begin() + b2, in.begin() + e2 + 1, val);
        int index = distance(in.begin(), it);

        // 计算左右子树的节点数
        int len1 = index - b2;
        int len2 = e2 - index;

        // 递归构造左右子树
        p->left = build(b1, b1 + len1 - 1, b2, index - 1);
        p->right = build(b1 + len1, e1 - 1, index + 1, e2);

        return p;
    }
};

class Solution 
{
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
    {
        return Solution1(inorder, postorder).solve();
    }
};

int main()
{
    Cases<vector<int>, vector<int>, TreeNode*> cases
    {
        {{}, {}, BuildTree({})},
        {{9,3,15,20,7}, {9,15,7,20,3}, BuildTree({3,9,20,null,null,15,7})},
    };

    test(&Solution::buildTree, cases, TreeEqual);

    return 0;
}