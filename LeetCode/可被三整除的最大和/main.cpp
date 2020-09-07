// https://leetcode-cn.com/problems/greatest-sum-divisible-by-three/

#include "../common/common.h"

class Solution 
{
public:
    int maxSumDivThree(vector<int>& nums) 
    {
        // dp[i][j]表示nums[0]~nums[i]可被3除余j的最大和
        vector<vector<int>> dp(nums.size(), vector<int>(3, 0));

        dp[0][nums[0] % 3] = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            for (int r = 0; r < 3; ++r)
            {
                dp[i][r] = dp[i - 1][r];
            }

            for (int r = 0; r < 3; ++r)
            {
                int t = dp[i - 1][r] + nums[i];
                dp[i][t % 3] = max(dp[i][t % 3], t);
            }
        }

        return dp[nums.size() - 1][0];
    }
};

int main()
{
    vector<int> nums{ 3,6,5,1,8 };
    TEST(Assert::areEqual(Solution().maxSumDivThree(nums), 18));

    nums = vector<int>{ 4 };
    TEST(Assert::areEqual(Solution().maxSumDivThree(nums), 0));

    nums = vector<int>{ 1,2,3,4,4 };
    TEST(Assert::areEqual(Solution().maxSumDivThree(nums), 12));

	return 0;
}