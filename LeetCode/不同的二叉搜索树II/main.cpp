// https://leetcode-cn.com/problems/unique-binary-search-trees-ii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(int n) : n(n) {}

    vector<TreeNode*> solve()
    {
        if (n == 0) return {};
        return build(1, n);
    }

private:
    int n;

    // 生成从a到b的节点可组成的所有二叉搜索树
    vector<TreeNode*> build(int a, int b)
    {
        if (a > b) return { NULL };
        if (a == b) return { new TreeNode(a) };

        vector<TreeNode*> ret;
        for (int r = a; r <= b; ++r)
        {
            vector<TreeNode*> v1 = build(a, r - 1);
            vector<TreeNode*> v2 = build(r + 1, b);
            for (TreeNode* left : v1)
            {
                for (TreeNode* right : v2)
                {
                    ret.push_back(new TreeNode(r, left, right));
                }
            }
        }

        return ret;
    }
};

class Solution 
{
public:
    vector<TreeNode*> generateTrees(int n) 
    {
        return Solution1(n).solve();
    }
};

bool correct(vector<TreeNode*> a, vector<TreeNode*> b)
{
    if (a.size() != b.size()) return false;
    for (int i = 0; i < (int)a.size(); ++i)
    {
        bool find = false;
        for (TreeNode* p : b)
        {
            if (TreeEqual(a[i], p))
            {
                find = true;
                break;
            }
        }
        if (!find) return false;
    }
    return true;
}

int main()
{
    Cases<int, vector<TreeNode*>> cases
    {
        {0, {}},
        {3, 
            {
                BuildTree({1,null,3,2}),
                BuildTree({3,2,null,1}),
                BuildTree({3,1,null,null,2}),
                BuildTree({2,1,3}),
                BuildTree({1,null,2,null,3}),
            }
        },
    };

    test(&Solution::generateTrees, cases, correct);

	return 0;
}