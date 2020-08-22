// https://leetcode-cn.com/problems/coin-lcci/

#include "../common/common.h"

class Solution
{
    int solution1(int n)
    {
        int MOD = 1000000007;
        int coins[] = { 25, 10, 5, 1 };

        vector<vector<int>> dp(4, vector<int>(n + 1, 0));

        for (int i = 0; i <= n; ++i)
        {
            if (i % coins[0] == 0)
            {
                dp[0][i] = 1;
            }
            else
            {
                dp[0][i] = 0;
            }
        }

        for (int i = 1; i < 4; ++i)
        {
            dp[i][0] = 1;
        }

        for (int i = 1; i < 4; ++i)
        {
            for (int j = coins[i]; j <= n; ++j)
            {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - coins[i]]) % MOD;
            }
        }

        return dp[3][n];
    }

    int solution2(int n)
    {
        int MOD = 1000000007;
        int coins[] = { 25, 10, 5, 1 };

        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = coins[i]; j <= n; ++j)
            {
                dp[j] = (dp[j] + dp[j - coins[i]]) % MOD;
            }
        }

        return dp[n];
    }

public:
    int waysToChange(int n)
    {
        return solution2(n);
    }
};

int main()
{
    assert(Solution().waysToChange(5) == 2);
    assert(Solution().waysToChange(10) == 4);

	return 0;
}