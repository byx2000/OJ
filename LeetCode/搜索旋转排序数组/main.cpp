// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        int left = 0, right = nums.size() - 1;

        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) return mid;
            
            if (nums[mid] > nums[left]) // midÎ»ÓÚ×ó°ë¶ÎÉýÐò
            {
                if (target > nums[mid]) left = mid + 1;
                else if (target < nums[left]) left = mid + 1;
                else right = mid - 1;
            }
            else // midÎ»ÓÚÓÒ°ë¶ÎÉýÐò
            {
                if (target >= nums[left]) right = mid - 1;
                else if (target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
        }

        for (int i = left; i <= right; ++i)
        {
            if (nums[i] == target) return i;
        }

        return -1;
    }

private:
    vector<int> nums;
    int target;
};

class Solution 
{
public:
    int search(vector<int>& nums, int target) 
    {
        return Solution1(nums, target).solve();
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{6,7,1,2,3,4,5}, 6, 0},
        {{4,5,6,7,0,1,2}, 4, 0},
        {{4,5,6,7,0,1,2}, 0, 4},
        {{4,5,6,7,0,1,2}, 3, -1},
        {{1}, 0, -1},
    };

    test(&Solution::search, cases);

	return 0;
}