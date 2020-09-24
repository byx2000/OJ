// https://leetcode-cn.com/problems/knight-dialer/

#include "../common/common.h"

class Solution 
{
public:
    int knightDialer(int n) 
    {
        static vector<vector<int>> last
        {
            {4, 6},
            {6, 8},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            { },
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4},
        };

        static const long long MOD = 1000000007;

        vector<long long> dp(10, 1);

        for (int c = 2; c <= n; ++c)
        {
            vector<long long> t = dp;
            for (int i = 0; i <= 9; ++i)
            {
                dp[i] = 0;
                for (int j : last[i])
                {
                    dp[i] = (dp[i] + t[j]) % MOD;
                }
            }
        }

        long long result = 0;
        for (int i = 0; i < 10; ++i)
        {
            result = (result + dp[i]) % MOD;
        }

        return (int)result;
    }
};

int main()
{
    Cases<int, int> cases
    {
        {1, 10},
        {2, 20},
        {3, 46},
    };

    test(&Solution::knightDialer, cases);

	return 0;
}