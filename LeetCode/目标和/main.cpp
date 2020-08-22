// https://leetcode-cn.com/problems/target-sum/

#include "../common/common.h"

class Solution
{
    vector<int> nums;
    map<pair<int, long long>, int> cache;

    int dp(int iNum, long long sum)
    {
        pair<int, long long> key(iNum, sum);

        if (cache.count(key) > 0)
        {
            return cache[key];
        }

        if (iNum == 0)
        {
            if (nums[0] == sum || nums[0] == -sum)
            {
                return nums[0] == 0 ? 2 : 1;
            }
            else
            {
                return 0;
            }
        }

        return cache[key] = dp(iNum - 1, sum + nums[iNum]) + dp(iNum - 1, sum - nums[iNum]);
    }

public:
    int findTargetSumWays(vector<int>& nums, int S)
    {
        this->nums = nums;
        return dp(nums.size() - 1, S);
    }
};

int main()
{
    vector<int> nums{ 1, 1, 1, 1, 1 };
    assert(Solution().findTargetSumWays(nums, 3) == 5);

	return 0;
}