// https://leetcode-cn.com/problems/find-peak-element/

#include "../common/common.h"

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        int left = 0, right = nums.size() - 1;

        // 每次循环开始时，left所在的位置为“上坡”，right所在的位置为“下坡”
        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            // mid所在位置为“上坡”，说明mid和right之间一定有“山峰”
            if (nums[mid] > nums[mid - 1]) left = mid;
            // 否则说明left和mid之间一定有“山峰”
            else right = mid;
        }

        for (int i = left + 1; i <= right; ++i)
        {
            if (nums[i] < nums[i - 1]) return i - 1;
        }

        return right;
    }
};

int main()
{
    // 无测试

	return 0;
}