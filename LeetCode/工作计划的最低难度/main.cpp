// https://leetcode-cn.com/problems/minimum-difficulty-of-a-job-schedule/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        if ((int)nums.size() < k)
        {
            return -1;
        }

        cache = vector<vector<int>>(nums.size(), vector<int>(k + 1, -1));
        int r = dp(nums.size() - 1, k);
        return r;
    }

private:
    vector<int> nums;
    int k;
    vector<vector<int>> cache;

    // 将nums[0]~nums[index]分成count份，每份最大值之和的最小值
    // 假设index + 1 >= count
    int dp(int index, int count)
    {
        if (cache[index][count] != -1)
        {
            return cache[index][count];
        }

        if (count == 1)
        {
            // 返回nums[0]~nums[index]的最大值
            return cache[index][count] = *max_element(nums.begin(), nums.begin() + index + 1);
        }

        if (index + 1 == count)
        {
            // 返回nums[0]~nums[index]的和
            return cache[index][count] = accumulate(nums.begin(), nums.begin() + index + 1, 0);
        }

        int maxVal = nums[index]; // nums[i]~nums[index]的最大值
        int ret = dp(index - 1, count - 1) + maxVal;
        for (int i = index - 1; i >= count - 1 && i >= 1; --i)
        {
            maxVal = max(maxVal, nums[i]);
            ret = min(ret, dp(i - 1, count - 1) + maxVal);
        }

        return cache[index][count] = ret;
    }
};

class Solution 
{
public:
    int minDifficulty(vector<int>& nums, int k) 
    {
        return Solution1(nums, k).solve();
    }
};

int main()
{
    vector<int> nums{ 1 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 1), 1));

    nums = vector<int>{ 1 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 2), -1));

    nums = vector<int>{ 1, 2 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 1), 2));

    nums = vector<int>{ 1, 2 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 2), 3));

    nums = vector<int>{ 1, 2 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 3), -1));

    nums = vector<int>{ 1, 2, 3 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 1), 3));

    nums = vector<int>{ 1, 2, 3 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 2), 4));

    nums = vector<int>{ 1, 2, 3 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 3), 6));

    nums = vector<int>{ 1, 2, 3 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 4), -1));

    nums = vector<int>{ 6,5,4,3,2,1 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 2), 7));

    nums = vector<int>{ 9,9,9 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 4), -1));

    nums = vector<int>{ 1,1,1 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 3), 3));

    nums = vector<int>{ 7,1,7,1,7,1 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 3), 15));

    nums = vector<int>{ 11,111,22,222,33,333,44,444 };
    TEST(Assert::areEqual(Solution().minDifficulty(nums, 6), 843));

	return 0;
}