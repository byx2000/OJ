// https://leetcode-cn.com/problems/split-array-largest-sum/

#include "../common/common.h"

// O(n^2k) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        prefixSum = vector<int>(nums.size());
        partial_sum(nums.begin(), nums.end(), prefixSum.begin());
        cache = vector<vector<int>>(nums.size(), vector<int>(k + 1, -1));
        return dp(nums.size() - 1, k);
    }

private:
    vector<int> nums;
    int k;
    vector<int> prefixSum; // 前缀和
    vector<vector<int>> cache;

    // nums[i]~nums[j]的和
    int sum(int i, int j)
    {
        return (i == 0) ? prefixSum[j] : prefixSum[j] - prefixSum[i - 1];
    }

    // 把nums[0]~nums[index]分成count份，每份和的最小值
    // 假设index + 1 >= count && count >= 1
    int dp(int index, int count)
    {
        if (cache[index][count] != -1)
        {
            return cache[index][count];
        }

        if (count == 1)
        {
            return cache[index][count] = sum(0, index);
        }

        int ret = max(dp(index - 1, count - 1), nums[index]);
        for (int i = index - 1; i >= count - 1 && i >= 1; --i)
        {
            ret = min(ret, max(dp(i - 1, count - 1), sum(i, index)));
        }

        return cache[index][count] = ret;
    }
};

class Solution 
{
public:
    int splitArray(vector<int>& nums, int k) 
    {
        return Solution1(nums, k).solve();
    }
};

int main()
{
    vector<int> nums{ 7,2,5,10,8 };
    TEST(Assert::areEqual(Solution().splitArray(nums, 2), 18));

	return 0;
}