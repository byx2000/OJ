// https://leetcode-cn.com/problems/2-keys-keyboard/

#include "../common/common.h"

// 解法1：动态规划
class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        cache = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        return dp(0, 1);
    }

private:
    int n;
    vector<vector<int>> cache;

    // 剪切板有k个A，当前有m个A，所需要的最少操作数
    int dp(int k, int m)
    {
        if (m == n)
        {
            return 0;
        }

        if (m > n)
        {
            return n + 1;
        }

        if (cache[k][m] != -1)
        {
            return cache[k][m];
        }

        int ret = dp(m, 2 * m) + 2; // 全选、粘贴
        if (k > 0)
        {
            ret = min(ret, dp(k, m + k) + 1); // 粘贴
        }

        return cache[k][m] = ret;
    }
};

class Solution
{
public:
    int minSteps(int n)
    {
        return Solution1(n).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minSteps(3), 3));
    TEST(Assert::areEqual(Solution().minSteps(10), 7));

    return 0;
}