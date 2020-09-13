// https://leetcode-cn.com/problems/predict-the-winner/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    bool solve()
    {
        cache = vector<vector<int>>(nums.size(), vector<int>(nums.size()));
        book = vector<vector<bool>>(nums.size(), vector<bool>(nums.size(), false));
        return dp(0, nums.size() - 1) >= 0;
    }

private:
    vector<int> nums;
    vector<vector<int>> cache;
    vector<vector<bool>> book;

    // 剩下nums[i]~nums[j]时，先手得分-后手得分的最大值
    int dp(int i, int j)
    {
        if (book[i][j])
        {
            return cache[i][j];
        }
        book[i][j] = true;

        if (i == j)
        {
            return cache[i][j] = nums[i];
        }
        
        return cache[i][j] = max(nums[i] - dp(i + 1, j), nums[j] - dp(i, j - 1));
    }
};

class Solution 
{
public:
    bool PredictTheWinner(vector<int>& nums) 
    {
        return Solution1(nums).solve();
    }
};

int main()
{
    vector<int> nums{ 1, 5, 2 };
    TEST(!Assert::isTrue(Solution().PredictTheWinner(nums)));

    nums = vector<int>{ 1, 5, 233, 7 };
    TEST(Assert::isTrue(Solution().PredictTheWinner(nums)));

	return 0;
}