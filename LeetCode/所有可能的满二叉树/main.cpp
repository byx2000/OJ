// https://leetcode-cn.com/problems/all-possible-full-binary-trees/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(int N) : N(N) {}

    vector<TreeNode*> solve()
    {
        if (N % 2 == 0) return {};
        return search(N);
    }

private:
    int N;

    // 返回节点数为n的所有完全二叉树
    // 假设n是奇数
    vector<TreeNode*> search(int n)
    {
        if (n == 1) return { new TreeNode(0) };

        vector<TreeNode*> ret;
        for (int i = 1; i <= n - 1; i += 2)
        {
            vector<TreeNode*> left = search(i);
            vector<TreeNode*> right = search(n - i - 1);
            for (TreeNode* p1 : left)
            {
                for (TreeNode* p2 : right)
                {
                    ret.push_back(new TreeNode(0, p1, p2));
                }
            }
        }

        return ret;
    }
};

class Solution 
{
public:
    vector<TreeNode*> allPossibleFBT(int N)
    {
        return Solution1(N).solve();
    }
};

bool check(vector<TreeNode*> a, vector<TreeNode*> b)
{
    if (a.size() != b.size()) return false;
    for (TreeNode* p1 : a)
    {
        bool find = false;
        for (TreeNode* p2 : b)
        {
            if (TreeEqual(p1, p2))
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
        {7, 
        {
            BuildTree({0,0,0,null,null,0,0,null,null,0,0}),
            BuildTree({0,0,0,null,null,0,0,0,0}),
            BuildTree({0,0,0,0,0,0,0}),
            BuildTree({0,0,0,0,0,null,null,null,null,0,0}),
            BuildTree({0,0,0,0,0,null,null,0,0}),
        }},
    };

    test(&Solution::allPossibleFBT, cases, check);

	return 0;
}