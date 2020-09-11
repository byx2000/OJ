// https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/

#include "../common/common.h"

// O(n^2)动态规划 超时
class Solution1
{
public:
    Solution1(const vector<int>& nums, int d)
        : nums(nums), d(d) {}

    int solve()
    {
        cache = vector<int>(nums.size(), -1);

        int result = 1;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            result = max(result, dp(i));
        }

        return result;
    }

private:
    vector<int> nums;
    int d;
    vector<int> cache;

    // 以nums[i]结尾的最长定差子序列长度
    int dp(int i)
    {
        if (cache[i] != -1)
        {
            return cache[i];
        }

        int ret = 1;
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] + d == nums[i])
            {
                ret = max(ret, dp(j) + 1);
            }
        }

        return cache[i] = ret;
    }
};

// 动态规划 + 哈希表
class Solution2
{
public:
    Solution2(const vector<int>& nums, int d)
        : nums(nums), d(d) {}

    int solve()
    {
        cache = vector<int>(nums.size(), -1);

        for (int i = 0; i < (int)nums.size(); ++i)
        {
            index[nums[i]].push_back(i);
        }

        int result = 1;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            result = max(result, dp(i));
        }

        return result;
    }

private:
    vector<int> nums;
    int d;
    unordered_map<int, vector<int>> index;
    vector<int> cache;

    // 以nums[i]结尾的最长定差子序列长度
    int dp(int i)
    {
        if (cache[i] != -1)
        {
            return cache[i];
        }

        int ret = 1;
        vector<int> ids = index[nums[i] - d];
        for (int j : ids)
        {
            if (j < i)
            {
                ret = max(ret, dp(j) + 1);
            }
        }

        return cache[i] = ret;
    }
};

// O(n) 动态规划
class Solution3
{
public:
    Solution3(const vector<int>& nums, int d)
        : nums(nums), d(d) {}

    int solve()
    {
        // hash[i]表示以i结尾的最长定差子序列长度
        unordered_map<int, int> hash;

        int result = 1;
        for (int n : nums)
        {
            result = max(result, hash[n] = hash[n - d] + 1);
        }

        return result;
    }

private:
    vector<int> nums;
    int d;
};

class Solution 
{
public:
    int longestSubsequence(vector<int>& nums, int d) 
    {
        //return Solution1(nums, d).solve();
        //return Solution2(nums, d).solve();
        return Solution3(nums, d).solve();
    }
};

int main()
{
    vector<int> nums{ 1,2,3,4 };
    TEST(Assert::areEqual(Solution().longestSubsequence(nums, 1), 4));

    nums = vector<int>{ 1,3,5,7 };
    TEST(Assert::areEqual(Solution().longestSubsequence(nums, 1), 1));

    nums = vector<int>{ 1,5,7,8,5,3,4,2,1 };
    TEST(Assert::areEqual(Solution().longestSubsequence(nums, -2), 4));

	return 0;
}