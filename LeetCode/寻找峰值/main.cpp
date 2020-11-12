// https://leetcode-cn.com/problems/find-peak-element/

#include "../common/common.h"

// 二分法
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
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

        for (int i = left + 1; i <= right - 1; ++i)
        {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) return i;
        }

        return (nums[left] > nums[right]) ? left : right;
    }

private:
    vector<int> nums;
};

// 三分法
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        int left = 0, right = nums.size() - 1;

        while (right - left > 3)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;
            if (nums[mid1] < nums[mid2]) left = mid1;
            else right = mid2;
        }

        for (int i = left + 1; i <= right - 1; ++i)
        {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) return i;
        }

        return (nums[left] > nums[right]) ? left : right;
    }

private:
    vector<int> nums;
};

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    // 无测试

	return 0;
}