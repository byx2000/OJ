// https://leetcode-cn.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/

#include "../common/common.h"

// O(n^2) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        cache = vector<int>(nums.size(), -1);
        return dp(nums.size() - 1);
    }

private:
    vector<int> nums;
    int target;
    vector<int> cache;

    // dp(i)：nums[0]~nums[i]中满足要求的子数组最大个数
    int dp(int i)
    {
        if (i < 0)
        {
            return 0;
        }

        if (cache[i] != -1)
        {
            return cache[i];
        }

        // 不选nums[i]
        int ret = dp(i - 1);

        // 寻找最大的j，使得nums[j] + nums[j + 1] + .. + nums[i] == target
        int j = i, s = 0;
        while (j >= 0)
        {
            s += nums[j];
            if (s == target)
            {
                return cache[i] = max(ret, dp(j - 1) + 1);
            }
            j--;
        }

        return cache[i] = ret;
    }
};

// O(n) 动态规划 前缀和、哈希表优化
class Solution2
{
public:
    Solution2(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        // dp[i]：nums[0]~nums[i]中满足要求的子数组最大个数
        vector<int> dp(nums.size());

        // preId[s] = i表示nums[0] + nums[1] + ... + nums[i] = s
        unordered_map<int, int> preId;

        dp[0] = (nums[0] == target) ? 1 : 0;
        int preSum = nums[0]; // 前缀和
        preId[preSum] = 0;
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            preSum += nums[i];
            
            dp[i] = dp[i - 1];
            if (preId.count(preSum - target) > 0)
            {
                dp[i] = max(dp[i], dp[preId[preSum - target]] + 1);
            }
            else if (preSum == target)
            {
                dp[i] = max(dp[i], 1);
            }
            
            preId[preSum] = i;
        }

        return dp.back();
    }

private:
    vector<int> nums;
    int target;
};

class Solution 
{
public:
    int maxNonOverlapping(vector<int>& nums, int target) 
    {
        //return Solution1(nums, target).solve();
        return Solution2(nums, target).solve();
    }
};

int main()
{
    vector<int> nums{ 1,1,1,1,1 };
    TEST(Assert::areEqual(Solution().maxNonOverlapping(nums, 2), 2));

    nums = vector<int>{ -1,3,5,1,4,2,-9 };
    TEST(Assert::areEqual(Solution().maxNonOverlapping(nums, 6), 2));

    nums = vector<int>{ -2,6,6,3,5,4,1,2,8 };
    TEST(Assert::areEqual(Solution().maxNonOverlapping(nums, 10), 3));

    nums = vector<int>{ 0,0,0 };
    TEST(Assert::areEqual(Solution().maxNonOverlapping(nums, 0), 3));

    nums = vector<int>{ -2,6,6,3,5,4,1,2,8 };
    TEST(Assert::areEqual(Solution().maxNonOverlapping(nums, 10), 3));

	return 0;
}