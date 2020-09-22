// https://leetcode-cn.com/problems/partition-array-for-maximum-sum/

#include "../common/common.h"

// 记忆化搜索
class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        cache = vector<int>(nums.size(), -1);
        return dp(nums.size() - 1);
    }

private:
    vector<int> nums;
    int k;
    vector<int> cache;

    // nums[0]~nums[i]的答案
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

        int ret = -1;
        int maxVal = nums[i];

        for (int j = i - 1; j >= i - k; --j)
        {
            ret = max(ret, dp(j) + maxVal * (i - j));
            if (j < 0)
            {
                break;
            }
            maxVal = max(maxVal, nums[j]);
        }

        return cache[i] = ret;
    }
};

class Solution 
{
public:
    int maxSumAfterPartitioning(vector<int>& nums, int k) 
    {
        return Solution1(nums, k).solve();
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{ 1,15,7,9,2,5,10 }, 3, 84},
    };

    test(&Solution::maxSumAfterPartitioning, cases);

	return 0;
}