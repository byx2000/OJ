// https://leetcode-cn.com/problems/minimum-size-subarray-sum/

#include "../common/common.h"

class Solution 
{
public:
    int minSubArrayLen(int target, vector<int>& nums) 
    {
        //return solution1(target, nums);
        return solution2(target, nums);
    }

    // 暴力法
    int solution1(int target, const vector<int>& nums)
    {
        int minLen = nums.size() + 1;

        for (int i = 0; i < (int)nums.size(); ++i)
        {
            int sum = 0;
            for (int j = i; j < (int)nums.size(); ++j)
            {
                sum += nums[j];
                if (j - i + 1 >= minLen) break;
                if (sum >= target)
                {
                    minLen = min(minLen, j - i + 1);
                    break;
                }
            }
        }

        return minLen == nums.size() + 1 ? 0 : minLen;
    }

    // 滑动窗口
    int solution2(int target, const vector<int>& nums)
    {
        int left = 0, right = 0, sum = 0, minLen = nums.size() + 1;

        while (true)
        {
            while (right < (int)nums.size() && sum < target)
            {
                sum += nums[right];
                right++;
            }

            if (sum >= target)
                minLen = min(minLen, right - left);

            while (sum >= target)
            {
                sum -= nums[left];
                left++;
            }

            minLen = min(minLen, right - left + 1);

            if (right == nums.size()) break;
        }

        return minLen == nums.size() + 1 ? 0 : minLen;
    }
};

int main()
{
    Cases<int, vector<int>, int> cases
    {
        {4, {1,4,4}, 1},
        {6, {1,1,1,1,1}, 0},
        {7, {2,3,1,2,4,3}, 2},
        {7, {2,3,1,4,3,2}, 2},
        {7, {4,3,1,2,3,2}, 2},
    };

    test(&Solution::minSubArrayLen, cases);

	return 0;
}