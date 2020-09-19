// https://leetcode-cn.com/problems/reducing-dishes/

#include "../common/common.h"

// O(n^2) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        sort(nums.begin(), nums.end());

        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size() + 1));
        book = vector<vector<bool>>(nums.size(), vector<bool>(nums.size() + 1, false));

        int result = 0;
        for (int c = 0; c <= (int)nums.size(); ++c)
        {
            result = max(result, dp(nums.size() - 1, c));
        }

        return result;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;
    vector<vector<bool>> book;

    // 在nums[0]~nums[i]中选c种菜品可得到的“喜爱时间”最大值
    // 假设i + 1 >= c
    int dp(int i, int c)
    {
        if (book[i][c])
        {
            return cache[i][c];
        }
        book[i][c] = true;

        if (i == 0)
        {
            return cache[i][c] = (c == 0) ? 0 : nums[i];
        }

        if (c == 0)
        {
            return cache[i][c] = 0;
        }

        int ret = c * nums[i] + dp(i - 1, c - 1);
        if (i + 1 > c)
        {
            ret = max(ret, dp(i - 1, c));
        }

        return cache[i][c] = ret;
    }
};

class Solution 
{
public:
    int maxSatisfaction(vector<int>& nums) 
    {
        return Solution1(nums).solve();
    }
};

int main()
{
    vector<int> nums{ -1,-8,0,5,-9 };
    TEST(Assert::areEqual(Solution().maxSatisfaction(nums), 14));

    nums = vector<int>{ 4,3,2 };
    TEST(Assert::areEqual(Solution().maxSatisfaction(nums), 20));

    nums = vector<int>{ -1,-4,-5 };
    TEST(Assert::areEqual(Solution().maxSatisfaction(nums), 0));

    nums = vector<int>{ -2,5,-1,0,3,-3 };
    TEST(Assert::areEqual(Solution().maxSatisfaction(nums), 35));

	return 0;
}