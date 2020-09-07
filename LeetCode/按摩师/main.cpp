// https://leetcode-cn.com/problems/the-masseuse-lcci/

#include "../common/common.h"

class Solution
{
public:
    int massage(vector<int>& nums)
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

        vector<int> dp(nums.size());

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < (int)nums.size(); ++i)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[nums.size() - 1];
    }
};

int main()
{
    vector<int> nums{ 1,2,3,1 };
    TEST(Assert::areEqual(Solution().massage(nums), 4));

    nums = vector<int>{ 2,7,9,3,1 };
    TEST(Assert::areEqual(Solution().massage(nums), 12));

    nums = vector<int>{ 2,1,4,5,3,1,1,3 };
    TEST(Assert::areEqual(Solution().massage(nums), 12));

	return 0;
}