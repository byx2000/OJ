// https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/

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

    // ��p�ڵ㿪ʼ��Ҷ�ڵ��·���Ͻڵ�ֵ֮�����ֵ
    int maxSum(TreeNode* p)
    {
        if (p == NULL) return 0;
        int left = max(maxSum(p->left) + p->val, p->val);
        int right = max(maxSum(p->right) + p->val, p->val);
        return max(left, right);
    }

    // ��������·���Ͻڵ�ֵ֮�����ֵ
    int dfs(TreeNode* p) 
    {
        if (p == NULL) return numeric_limits<int>::min();
        int left = maxSum(p->left);
        int right = maxSum(p->right);
        int sum = p->val;
        if (left > 0) sum += left;
        if (right > 0) sum += right;
        return max({ sum, dfs(p->left), dfs(p->right) });
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

    // ���� { ��pΪ��㵽Ҷ�ڵ��·���Ͻڵ�ֵ֮�����ֵ, ��������·���Ͻڵ�ֵ֮�����ֵ }
    pair<int, int> dfs(TreeNode* p)
    {
        if (p == NULL) return { 0, numeric_limits<int>::min() };
        pair<int, int> left = dfs(p->left);
        pair<int, int> right = dfs(p->right);
        int r1 = max(max(left.first + p->val, p->val), max(right.first + p->val, p->val));
        int sum = p->val;
        if (left.first > 0) sum += left.first;
        if (right.first > 0) sum += right.first;
        int r2 = max({ sum, left.second, right.second });
        return { r1, r2 };
    }
};

class Solution 
{
public:
    int maxPathSum(TreeNode* root) 
    {
        //return Solution1(root).solve();
        return Solution2(root).solve();
    }
};

int main()
{
    Cases<TreeNode*, int> cases
    {
        {BuildTree({1,2,3}), 6},
        {BuildTree({-10,9,20,null,null,15,7}), 42},
    };

    test(&Solution::maxPathSum, cases);

	return 0;
}