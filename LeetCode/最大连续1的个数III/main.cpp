// https://leetcode-cn.com/problems/max-consecutive-ones-iii/

#include "../common/common.h"

class Solution 
{
public:
    int longestOnes(vector<int>& nums, int k) 
    {
        int left = 0;
        int zeroCnt = 0;
        int maxLen = 0;

        for (int right = 0; right < (int)nums.size(); ++right)
        {
            if (nums[right] == 0)
            {
                zeroCnt++;
                while (zeroCnt > k)
                {
                    if (nums[left] == 0) zeroCnt--;
                    left++;
                }
            }

            // �˴�����ʽ��nums[left]~nums[right]����Ҫ��
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{1,1,1,0,0,0,1,1,1,1,0}, 2, 6},
        {{0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3, 10},
    };

    test(&Solution::longestOnes, cases);

	return 0;
}