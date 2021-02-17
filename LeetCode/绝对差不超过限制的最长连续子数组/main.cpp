// https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/

#include "../common/common.h"

class Solution 
{
public:
    int longestSubarray(vector<int>& nums, int limit) 
    {
        int left = 0, right = 0, maxLen = 0;
        multiset<int> m;

        m.insert(nums[0]);
        while (right < (int)nums.size())
        {
            do
            {
                right++; 
                if (right >= (int)nums.size()) break;
                m.insert(nums[right]);
            } while (right < (int)nums.size() && abs(*m.begin() - *m.rbegin()) <= limit);

            maxLen = max(maxLen, right - left);
            if (right == nums.size()) break;

            do
            {
                m.erase(m.find(nums[left]));
                left++;
            } while (abs(*m.begin() - *m.rbegin()) > limit);
        }

        return maxLen;
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{8}, 10, 1},
        {{8,2,4,7}, 4, 2},
        {{10,1,2,4,7,2}, 5, 4},
        {{4,2,2,2,4,4,2,2}, 0, 3},
    };

    test(&Solution::longestSubarray, cases);

	return 0;
}