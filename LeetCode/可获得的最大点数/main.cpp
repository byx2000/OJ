// https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/

#include "../common/common.h"

// O(n^2*k) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        cache = vector<vector<vector<int>>>(nums.size(), vector<vector<int>>(nums.size(), vector<int>(k + 1, -1)));
        return dp(0, nums.size() - 1, k);
    }

private:
    vector<int> nums;
    int k;
    vector<vector<vector<int>>> cache;

    // 在nums[i]~nums[j]中拿k张卡牌能获得的最大点数
    int dp(int i, int j, int k)
    {
        if (k == 0)
        {
            return 0;
        }

        if (cache[i][j][k] != -1)
        {
            return cache[i][j][k];
        }

        return cache[i][j][k] = max(dp(i + 1, j, k - 1) + nums[i], dp(i, j - 1, k - 1) + nums[j]);
    }
};

// O(n^2) 动态规划
class Solution2
{
public:
    Solution2(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));
        return dp(0, nums.size() - 1);
    }

private:
    vector<int> nums;
    int k;
    vector<vector<int>> cache;

    // 在nums[i]~nums[j]中拿k张卡牌能获得的最大点数
    int dp(int i, int j)
    {
        if (j - i + 1 == nums.size() - k)
        {
            return 0;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        return cache[i][j] = max(dp(i + 1, j) + nums[i], dp(i, j - 1) + nums[j]);
    }
};

// 转化为寻找长度为n-k的和最小的子数组
class Solution3
{
public:
    Solution3(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        // 求前缀和
        vector<int> prefixSum(nums.size());
        prefixSum[0] = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        int length = nums.size() - k;
        if (length == 0)
        {
            return prefixSum.back();
        }

        // 寻找长度为n-k的和最小的子数组
        int minSum = prefixSum[length - 1];
        for (int i = 1; i + length - 1 < (int)nums.size(); ++i)
        {
            minSum = min(minSum, prefixSum[i + length - 1] - prefixSum[i - 1]);
        }

        return prefixSum.back() - minSum;
    }

private:
    vector<int> nums;
    int k;
};

class Solution 
{
public:
    int maxScore(vector<int>& nums, int k) 
    {
        //return Solution1(nums, k).solve();
        //return Solution2(nums, k).solve();
        return Solution3(nums, k).solve();
    }
};

int main()
{
    vector<int> nums = BuildList({ 1,2,3,4,5,6,1 });
    int k = 3;
    int answer = 12;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

    nums = BuildList({ 2,2,2 });
    k = 2;
    answer = 4;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

    nums = BuildList({ 9,7,7,9,7,7,9 });
    k = 7;
    answer = 55;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

    nums = BuildList({ 1,1000,1 });
    k = 1;
    answer = 1;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

    nums = BuildList({ 1,1000,1 });
    k = 1;
    answer = 1;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

    nums = BuildList({ 1,79,80,1,1,1,200,1 });
    k = 3;
    answer = 202;
    TEST(Assert::areEqual(Solution().maxScore(nums, k), answer));

	return 0;
}