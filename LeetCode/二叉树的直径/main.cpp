// https://leetcode-cn.com/problems/diameter-of-binary-tree/

#include "../common/common.h"

// ˫��dfs
class Solution1
{
public:
    Solution1(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root);
    }

private:
    TreeNode* root;

    // p�ĸ߶�
    int height(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max(height(p->left), height(p->right)) + 1;
    }

    // p�е��·��
    // �ȼ�����p���������������������߶�֮�����ֵ
    int dfs(TreeNode* p)
    {
        if (p == NULL) return 0;
        return max({ height(p->left) + height(p->right), dfs(p->left), dfs(p->right) });
    }
};

// һ�α���
class Solution2
{
public:
    Solution2(TreeNode* root) : root(root) {}

    int solve()
    {
        return dfs(root).second;
    }

private:
    TreeNode* root;

    // ���� { p�ĸ߶�, p���������������������߶�֮�����ֵ }
    pair<int, int> dfs(TreeNode* p)
    {
        if (p == NULL) return { 0, 0 };
        pair<int, int> left = dfs(p->left);
        pair<int, int> right = dfs(p->right);
        return { max(left.first, right.first) + 1, max({left.first + right.first, left.second, right.second}) };
    }
};

class Solution 
{
public:
    int diameterOfBinaryTree(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({ 1,2,3,4,5 }), 3},
    };

    test(&Solution::diameterOfBinaryTree, cases);

	return 0;
}