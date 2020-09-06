// https://leetcode-cn.com/problems/wiggle-subsequence/

#include "../common/common.h"

// 解法1：O(n^2) dp
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

// 解法2：O(n) dp
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        vector<int> up(nums.size(), 1);
        vector<int> down(nums.size(), 1);

        for (int i = 1; i < (int)nums.size(); ++i)
        {
            if (nums[i] > nums[i - 1])
            {
                up[i] = down[i - 1] + 1;
                down[i] = down[i - 1];
            }
            else if (nums[i] < nums[i - 1])
            {
                up[i] = up[i - 1];
                down[i] = up[i - 1] + 1;
            }
            else
            {
                up[i] = up[i - 1];
                down[i] = down[i - 1];
            }
        }

        return max(up.back(), down.back());
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
    vector<int> input{ 1, 7, 4, 9, 2, 5 };
    TEST(Assert::areEqual(Solution().wiggleMaxLength(input), 6));

    input = vector<int>{ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
    TEST(Assert::areEqual(Solution().wiggleMaxLength(input), 7));

    input = vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TEST(Assert::areEqual(Solution().wiggleMaxLength(input), 2));


	return 0;
}