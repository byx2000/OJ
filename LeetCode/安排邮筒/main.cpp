// https://leetcode-cn.com/problems/allocate-mailboxes/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        sort(nums.begin(), nums.end());
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

    int sum(int i, int j)
    {
        return (i == 0) ? prefixSum[j] : prefixSum[j] - prefixSum[i - 1];
    }

    int dist(int i, int j)
    {
        if (i == j)
        {
            return 0;
        }
        
        int mid = (i + j) / 2;
        if ((j - i + 1) % 2 == 0)
        {
            return sum(mid + 1, j) - sum(i, mid);
        }
        else
        {
            return sum(mid + 1, j) - sum(i, mid - 1);
        }
    }

    // 将nums[0]~nums[index]分成count份，每份dist总和的最小值
    // 假设 index + 1 >= count 且 count >= 1
    int dp(int index, int count)
    {
        if (cache[index][count] != -1)
        {
            return cache[index][count];
        }

        if (count == 1)
        {
            return cache[index][count] = dist(0, index);
        }

        int ret = dp(index - 1, count - 1);
        for (int i = index - 1; i >= count - 1 && i >= 1; --i)
        {
            ret = min(ret, dp(i - 1, count - 1) + dist(i, index));
        }

        return cache[index][count] = ret;
    }
};

class Solution
{
public:
    int minDistance(vector<int>& nums, int k)
    {
        return Solution1(nums, k).solve();
    }
};

int main()
{
    vector<int> nums{ 1,4,8,10,20 };
    TEST(Assert::areEqual(Solution().minDistance(nums, 3), 5));

    nums = vector<int>{ 2,3,5,12,18 };
    TEST(Assert::areEqual(Solution().minDistance(nums, 2), 9));

    nums = vector<int>{ 7,4,6,1 };
    TEST(Assert::areEqual(Solution().minDistance(nums, 1), 8));

    nums = vector<int>{ 3,6,14,10 };
    TEST(Assert::areEqual(Solution().minDistance(nums, 4), 0));

	return 0;
}