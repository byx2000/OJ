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
        int left = 0, right = -1, sum = 0, minLen = nums.size() + 1;
        while (true)
        {
            right++;
            while (right < (int)nums.size())
            {
                sum += nums[right];
                if (sum >= target) break;
                right++;
            }

            // 此时nums[left] + ... + nums[right] >= target
            // 且nums[left] + ... + nums[right-1] < target

            minLen = min(minLen, right - left + 1);

            while (left <= right)
            {
                sum -= nums[left];
                left++;
                if (sum < target) break;
            }

            // 此时nums[left] + ... + nums[right] < target
            // 且nums[left-1] + ... + nums[right] >= target

            minLen = min(minLen, right - left + 2);

            if (right == nums.size() - 1 || right == nums.size()) break;
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
    };

    test(&Solution::minSubArrayLen, cases);

	return 0;
}