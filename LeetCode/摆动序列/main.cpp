// https://leetcode-cn.com/problems/wiggle-subsequence/

#include "../common/common.h"

// ½â·¨1£ºO(n^2) dp
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        vector<int> up(nums.size(), 1);
        vector<int> down(nums.size(), 1);

        up[0] = down[0] = 1;
        int res = 1;
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    up[i] = max(up[i], down[j] + 1);
                }
                else if (nums[i] < nums[j])
                {
                    down[i] = max(down[i], up[j] + 1);
                }
            }

            res = max(res, up[i]);
            res = max(res, down[i]);
        }

        return res;
    }

private:
    vector<int> nums;
};

class Solution
{
public:
    int wiggleMaxLength(vector<int>& nums)
    {
        return Solution1(nums).solve();
    }
};

int main()
{
	return 0;
}