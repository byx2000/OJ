// https://leetcode-cn.com/problems/longest-arithmetic-subsequence/

#include "../common/common.h"

// O(n^3) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        int result = 2;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    // 以nums[i]、nums[j]结尾的最长等差子序列长度
    // 假设 i < j
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 2;
        for (int k = 0; k < i; ++k)
        {
            if (nums[j] - nums[i] == nums[i] - nums[k])
            {
                ret = max(ret, dp(k, i) + 1);
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^3) 动态规划 优化
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        int result = 2;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    // 以nums[i]、nums[j]结尾的最长等差子序列长度
    // 假设 i < j
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 2;
        for (int k = i - 1; k >= 0; --k)
        {
            if (nums[j] - nums[i] == nums[i] - nums[k])
            {
                ret = max(ret, dp(k, i) + 1);
                break;
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^3) 动态规划 哈希表优化
class Solution3
{
public:
    Solution3(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            index[nums[i]].push_back(i);
        }

        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        int result = 2;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> nums;
    unordered_map<int, vector<int>> index;
    vector<vector<int>> cache;

    // 以nums[i]、nums[j]结尾的最长等差子序列长度
    // 假设 i < j
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 2;
        for (int k : index[2 * nums[i] - nums[j]])
        {
            if (k < i)
            {
                ret = max(ret, dp(k, i) + 1);
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^2) 动态规划 哈希优化
class Solution4
{
public:
    Solution4(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        for (int n : nums)
        {
            if (index.count(n) > 0)
            {
                continue;
            }

            index[n][0] = -1;
            for (int i = 1; i < (int)nums.size(); ++i)
            {
                if (nums[i - 1] == n)
                {
                    index[n][i] = i - 1;
                }
                else
                {
                    index[n][i] = index[n][i - 1];
                }
            }
        }

        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        int result = 2;
        for (int i = 0; i < (int)nums.size() - 1; ++i)
        {
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> nums;
    unordered_map<int, unordered_map<int, int>> index;
    vector<vector<int>> cache;

    // 以nums[i]、nums[j]结尾的最长等差子序列长度
    // 假设 i < j
    int dp(int i, int j)
    {
        
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        int ret = 2;
        int target = 2 * nums[i] - nums[j];
        if (index.count(target) > 0)
        {
            int k = index[target][i];
            if (k != -1)
            {
                ret = dp(k, i) + 1;
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^2) 动态规划
class Solution5
{
public:
    Solution5(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(20001, -1));

        int result = 2;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            for (int d = -10000; d <= 10000; ++d)
            {
                result = max(result, dp(i, d));
            }
        }

        return result;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    // 以nums[i]结尾，公差为d的最长等差子序列长度
    int dp(int i, int d)
    {
        if (cache[i][d + 10000] != -1)
        {
            return cache[i][d + 10000];
        }

        int ret = 1;
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] - nums[j] == d)
            {
                ret = max(ret, dp(j, d) + 1);
            }
        }

        return cache[i][d + 10000] = ret;
    }
};

class Solution 
{
public:
    int longestArithSeqLength(vector<int>& nums)
    {
        //return Solution1(nums).solve();
        //return Solution2(nums).solve();
        //return Solution3(nums).solve();
        //return Solution4(nums).solve();
        return Solution5(nums).solve();
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{ 1, 2 }, 2},
        {{ 2, 2 }, 2},
        {{ 1, 2, 3 }, 3},
        {{ 3, 2, 1 }, 3},
        {{ 1, 2, -1 }, 2},
        {{ 1, 2, 3, 4 }, 4},
        {{ 1, 2, 4, 3 }, 3},
        {{ 4, 1, 2, 3 }, 3},
        {{ 1, 1, 0, 1 }, 3},
        {{ 3,6,9,12 }, 4},
        {{ 9,4,7,2,10 }, 3},
        {{ 20,1,15,3,10,5,8 }, 4},
    };

    test(&Solution::longestArithSeqLength, cases);

	return 0;
}