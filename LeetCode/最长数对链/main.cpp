// https://leetcode-cn.com/problems/maximum-length-of-pair-chain/

#include "../common/common.h"

class Solution 
{
public:
    int findLongestChain(vector<vector<int>>& pairs) 
    {
        sort(pairs.begin(), pairs.end());

        vector<int> dp(pairs.size(), 1);
        int result = 1;
        for (int i = 1; i < (int)pairs.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (pairs[j][1] < pairs[i][0])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = max(result, dp[i]);
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> pairs =
    {
        {1, 2},
        {2, 3},
        {3, 4},
    };
    TEST(Assert::areEqual(Solution().findLongestChain(pairs), 2));

    pairs = vector<vector<int>>
    {
        {3, 4},
        {2, 3},
        {1, 2},
    };
    TEST(Assert::areEqual(Solution().findLongestChain(pairs), 2));

	return 0;
}