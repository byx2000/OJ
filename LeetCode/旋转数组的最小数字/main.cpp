// https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/

#include "../common/common.h"

class Solution 
{
public:
    int minArray(vector<int>& nums) 
    {
        int left = 0, right = nums.size() - 1;
        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;
            else if (nums[mid] < nums[right])
                right = mid;
            else
                right--;
        }

        int minVal = nums[left];
        for (int i = left + 1; i <= right; ++i)
        {
            minVal = min(minVal, nums[i]);
        }

        return minVal;
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{3,4,5,1,2}, 1},
        {{2,2,2,0,1}, 0},
        {{1,10,10,10,10}, 1},
    };

    test(&Solution::minArray, cases);

	return 0;
}