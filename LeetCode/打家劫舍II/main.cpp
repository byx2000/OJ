// https://leetcode-cn.com/problems/house-robber-ii/

#include "../common/common.h"

class Solution
{
public:
    int rob(vector<int>& nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        else if (nums.size() == 1)
        {
            return nums[0];
        }
        else if (nums.size() == 2)
        {
            return max(nums[0], nums[1]);
        }

        vector<int> dp(nums.size() - 1);

        // 第一种情况
        int last = nums.back();
        nums.pop_back();
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < (int)dp.size(); ++i)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        int result1 = dp.back();

        // 第二种情况
        nums.push_back(last);
        nums.erase(nums.begin());
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < (int)dp.size(); ++i)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        int result2 = dp.back();

        return max(result1, result2);
    }
};

int main()
{
    vector<int> nums{ 2,3,2 };
    TEST(Assert::areEqual(Solution().rob(nums), 3));

    nums = vector<int>{ 1,2,3,1 };
    TEST(Assert::areEqual(Solution().rob(nums), 4));

	return 0;
}