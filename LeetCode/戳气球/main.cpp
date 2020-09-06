// https://leetcode-cn.com/problems/burst-balloons/

#include "../common/common.h"

// 解法1：记忆化搜索
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums)
    {
        this->nums.insert(this->nums.begin(), 1);
        this->nums.push_back(1);

    }

    int solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));
        return dp(0, nums.size() - 1);
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;

    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (j - i < 2)
        {
            return cache[i][j] = 0;
        }
        else if (j - i == 2)
        {
            return cache[i][j] = nums[i] * nums[i + 1] * nums[j];
        }
        else
        {
            int ret = -1;
            for (int k = i + 1; k < j; ++k)
            {
                ret = max(ret, dp(i, k) + dp(k, j) + nums[i] * nums[k] * nums[j]);
            }

            return cache[i][j] = ret;
        }
    }
};

class Solution
{
public:
    int maxCoins(vector<int>& nums)
    {
        return Solution1(nums).solve();
    }
};

int main()
{
    vector<int> input{ 3, 1, 5, 8 };
    TEST(Assert::areEqual(Solution().maxCoins(input), 167));

    input = vector<int>{ 8, 2, 6, 8, 9, 8, 1, 4, 1, 5, 3, 0, 7, 7, 0, 4, 2, 2 };
    TEST(Assert::areEqual(Solution().maxCoins(input), 3446));

	return 0;
}