// https://leetcode-cn.com/problems/count-vowels-permutation/

#include "../common/common.h"

class Solution 
{
public:
    int countVowelPermutation(int n) 
    {
        static const long long MOD = 1000000007;

        vector<long long> dp{ 1, 1, 1, 1, 1 };

        for (int i = 2; i <= n; ++i)
        {
            vector<long long> t = dp;
            dp[0] = (t[1] + t[2] + t[4]) % MOD;
            dp[1] = (t[0] + t[2]) % MOD;
            dp[2] = (t[1] + t[3]) % MOD;
            dp[3] = t[2] % MOD;
            dp[4] = (t[2] + t[3]) % MOD;
        }

        return (dp[0] + dp[1] + dp[2] + dp[3] + dp[4]) % MOD;
    }
};

int main()
{
    Cases<int, int> cases
    {
        {1, 5},
        {2, 10},
        {5, 68},
    };

    test(&Solution::countVowelPermutation, cases);

	return 0;
}