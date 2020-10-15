// https://leetcode-cn.com/problems/unique-binary-search-trees/

#include "../common/common.h"

// 动态规划
class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        cache = vector<int>(n + 1, -1);
        return dp(n);
    }

private:
    int n;
    vector<int> cache;

    // n个节点的不同二叉搜索树个数
    int dp(int n)
    {
        if (cache[n] != -1) return cache[n];

        if (n == 0 || n == 1) return cache[n] = 1;

        int cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            cnt += dp(i - 1) * dp(n - i);
        }
        return cache[n] = cnt;
    }
};

class Solution 
{
public:
    int numTrees(int n) 
    {
        return Solution1(n).solve();
    }
};

int main()
{
    Cases<int, int> cases
    {
        {3, 5},
        {4, 14},
        {5, 42},
        {15, 9694845},
    };

    test(&Solution::numTrees, cases);

	return 0;
}