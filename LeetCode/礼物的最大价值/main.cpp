// https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof/

#include "../common/common.h"

class Solution 
{
public:
    int maxValue(vector<vector<int>>& nums) 
    {
        this->nums = nums;
        cache = vector<vector<int>>(nums.size(), vector<int>(nums[0].size(), -1));
        return dp(nums.size() - 1, nums[0].size() - 1);
    }

private:
    vector<vector<int>> nums;
    vector<vector<int>> cache;

    int dp(int i, int j)
    {
        if (i < 0 || j < 0)
        {
            return 0;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (i == 0)
        {
            return cache[i][j] = dp(i, j - 1) + nums[i][j];
        }
        else if (j == 0)
        {
            return cache[i][j] = dp(i - 1, j) + nums[i][j];
        }
        else
        {
            return cache[i][j] = max(dp(i - 1, j), dp(i, j - 1)) + nums[i][j];
        }
    }
};

int main()
{
    vector<vector<int>> nums
    {
        {1,3,1},
        {1,5,1},
        {4,2,1},
    };
    TEST(Assert::areEqual(Solution().maxValue(nums), 12));
  
	return 0;
}