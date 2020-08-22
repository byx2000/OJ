// https://leetcode-cn.com/problems/partition-equal-subset-sum/

#include "../common/common.h"

class Solution
{
    vector<int> nums;
    vector<vector<bool>> cache;
    vector<vector<bool>> book;

    bool dp(int iNum, int s)
    {
        if (iNum == 0)
        {
            return nums[0] == s;
        }

        if (s <= 0)
        {
            return false;
        }

        if (book[iNum][s])
        {
            return cache[iNum][s];
        }

        book[iNum][s] = true;
        return cache[iNum][s] = dp(iNum - 1, s) || dp(iNum - 1, s - nums[iNum]);
    }

public:
    bool canPartition(vector<int>& nums)
    {
        int sum = 0;
        for (int i : nums)
        {
            sum += i;
        }

        this->nums = nums;

        if (sum % 2 != 0)
        {
            return false;
        }

        cache = vector<vector<bool>>(nums.size(), vector<bool>(sum / 2 + 1, false));
        book = vector<vector<bool>>(nums.size(), vector<bool>(sum / 2 + 1, false));

        return dp(nums.size() - 1, sum / 2);
    }
};

int main()
{
    vector<int> v{ 1, 5, 11, 5 };
    assert(Solution().canPartition(v));
    v = vector<int>{ 1, 2, 3, 5 };
    assert(!Solution().canPartition(v));

	return 0;
}