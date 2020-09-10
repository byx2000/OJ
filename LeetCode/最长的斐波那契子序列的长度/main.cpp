// https://leetcode-cn.com/problems/length-of-longest-fibonacci-subsequence/

#include "../common/common.h"

// O(n^3) 超时
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        int result = 0;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return (result == 0) ? 0 : result + 2;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    // 以nums[i]、nums[j]结尾的最长Fib序列长度-2
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 0;
        for (int k = 0; k < i; ++k)
        {
            if (nums[k] + nums[i] == nums[j])
            {
                ret = max(ret, dp(k, i) + 1);
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^2) 通过
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        for (int i = 0; i < (int)nums.size(); ++i)
        {
            index[nums[i]] = i;
        }

        int result = 0;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return (result == 0) ? 0 : result + 2;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;
    unordered_map<int, int> index;

    // 以nums[i]、nums[j]结尾的最长Fib序列长度-2
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 0;
        if (nums[j] - nums[i] < nums[i] && index.count(nums[j] - nums[i]) > 0)
        {
            int k = index[nums[j] - nums[i]];
            ret = dp(k, i) + 1;
        }

        return cache[i][j] = ret;
    }
};

class Solution 
{
public:
    int lenLongestFibSubseq(vector<int>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    vector<int> nums{ 1,2,3,4,5,6,7,8 };
    TEST(Assert::areEqual(Solution().lenLongestFibSubseq(nums), 5));

    nums = vector<int>{ 1,3,7,11,12,14,18 };
    TEST(Assert::areEqual(Solution().lenLongestFibSubseq(nums), 3));

	return 0;
}