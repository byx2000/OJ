// https://leetcode-cn.com/problems/longest-subarray-of-1s-after-deleting-one-element/

#include "../common/common.h"

class Solution 
{
public:
    int longestSubarray(vector<int>& nums) 
    {
        int left = 0, right = 0;
        int zeroCount = 0;
        
        while (right < (int)nums.size())
        {
            if (nums[right] == 0)
            {
                zeroCount++;
                break;
            }
            right++;
        }

        // nums全为1
        if (right == nums.size()) return nums.size() - 1;
        if (right == nums.size() - 1) return nums.size() - 1;

        int maxLen = right - left + 1;
        for (right++; right < (int)nums.size(); ++right)
        {
            if (nums[right] == 0)
            {
                while (nums[left] != 0) left++;
                left++;
            }

            // 此处不变式：nums[left]~nums[right]只有1个0
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen - 1;
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{1,0,0,0,0}, 1},
        {{1,1,0,1}, 3},
        {{0,1,1,1,0,1,1,0,1}, 5},
        {{1,1,1}, 2},
        {{1,1,0,0,1,1,1,0,1}, 4},
        {{0,0,0}, 0},
    };

    test(&Solution::longestSubarray, cases);

	return 0;
}