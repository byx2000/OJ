// https://leetcode-cn.com/problems/last-stone-weight-ii/
// 01背包问题变形

#include "../common/common.h"

class Solution
{
public:
    int lastStoneWeightII(vector<int>& stones)
    {
        nums = stones;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        cache = vector<vector<int>>(nums.size(), vector<int>(sum / 2 + 1, -1));
        int s1 = dp(nums.size() - 1, sum / 2);
        int s2 = sum - s1;
        return abs(s1 - s2);
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    // 将nums[0]~nums[index]装入space空间的背包的最大重量
    int dp(int index, int space)
    {
        if (index == 0)
        {
            if (space < nums[index])
            {
                return 0;
            }
            return nums[index];
        }

        if (cache[index][space] != -1)
        {
            return cache[index][space];
        }

        int ret = dp(index - 1, space);
        if (space >= nums[index])
        {
            ret = max(ret, dp(index - 1, space - nums[index]) + nums[index]);
        }

        return cache[index][space] = ret;
    }
};

int main()
{
    vector<int> nums{ 2,7,4,1,8,1 };
    TEST(Assert::areEqual(Solution().lastStoneWeightII(nums), 1));

    nums = vector<int>{ 14,1,7,17,8,10 };
    TEST(Assert::areEqual(Solution().lastStoneWeightII(nums), 1));

	return 0;
}