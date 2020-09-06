// https://leetcode-cn.com/problems/three-steps-problem-lcci/

#include "../common/common.h"

class Solution
{
public:
    int waysToStep(int n)
    {
        static int MOD = 1000000007;

        long long dp[4] = { 1, 2, 4, 0 };

        if (n <= 3)
        {
            return (int)dp[n - 1];
        }

        for (int i = 3; i < n; ++i)
        {
            dp[3] = (dp[0] + dp[1] + dp[2]) % MOD;
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = dp[3];
        }

        return (int)dp[3];
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().waysToStep(3), 4));
    TEST(Assert::areEqual(Solution().waysToStep(5), 13));

    return 0;
}