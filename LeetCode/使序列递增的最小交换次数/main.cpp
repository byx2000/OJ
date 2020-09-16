// https://leetcode-cn.com/problems/minimum-swaps-to-make-sequences-increasing/

#include "../common/common.h"

class Solution 
{
public:
    int minSwap(vector<int>& a, vector<int>& b) 
    {
        // 为保证有解，对任意a[i-1]、a[i]和b[i-1]、b[i]，有
        // (a[i] > a[i-1] && b[i] > b[i-1]) || (a[i] > b[i-1] && b[i] > a[i-1])

        // dp[i][0]：让a[0]~a[i]、b[0]~b[i]严格递增且不交换a[i]和b[i]的最少交换次数
        // dp[i][1]：让a[0]~a[i]、b[0]~b[i]严格递增且交换a[i]和b[i]的最少交换次数
        int n = a.size();
        vector<vector<int>> dp(n, vector<int>(2, numeric_limits<int>::max()));

        dp[0][0] = 0;
        dp[0][1] = 1;
        for (int i = 1; i < n; ++i)
        {
            if (a[i] > a[i - 1] && b[i] > b[i - 1])
            {
                dp[i][0] = min(dp[i][0], dp[i - 1][0]);
                dp[i][1] = min(dp[i][1], dp[i - 1][1] + 1);
            }
            if (a[i] > b[i - 1] && b[i] > a[i - 1])
            {
                dp[i][0] = min(dp[i][0], dp[i - 1][1]);
                dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
            }
        }

        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};

int main()
{
    vector<int> a{ 1,3,5,4 };
    vector<int> b{ 1,2,3,7 };
    TEST(Assert::areEqual(Solution().minSwap(a, b), 1));

    a = vector<int>{ 0,4,4,5,9 };
    b = vector<int>{ 0,1,6,8,10 };
    TEST(Assert::areEqual(Solution().minSwap(a, b), 1));

	return 0;
}