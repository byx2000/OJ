// https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/

#include "../common/common.h"

class Solution 
{
public:
    bool search(vector<int>& nums, int target) 
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right) 
        {
            while (left != right && nums[left] == nums[right]) right--;
            int mid = (left + right) / 2;
            if (nums[mid] == target) return true;
            else if (nums[mid] > target) 
            {
                if (nums[mid] > nums[right] && target < nums[left]) left = mid + 1;
                else right = mid - 1;
            }
            else 
            {
                if (nums[mid] < nums[left] && target > nums[right]) right = mid - 1;
                else left = mid + 1;
            }
        }
        return false;
    }
};

int main()
{
    Cases<vector<int>, int, bool> cases
    {
        {{10,10,10,-10,-10,-10,-10,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-8,-7,-7,-7,-7,-6,-6,-6,-5,-5,-5,-4,-4,-4,-4,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,7,7,8,8,8,8,9,9,9,9,9,9,9,10,10}, -6, true},
        {{-9,-9,-9,-8,-8,-7,-7,-7,-7,-6,-6,-6,-6,-6,-6,-6,-6,-6,-5,-5,-5,-5,-5,-4,-4,-4,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,0,0,0,1,1,2,2,2,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,7,7,7,7,7,8,9,9,9,10,10,10,10,10,10,10,-10,-9,-9,-9,-9}, 2, true},
        {{1,0,1,1,1}, 0, true},
        {{2,5,6,0,0,1,2}, 0, true},
        {{2,5,6,0,0,1,2}, 3, false},
    };

    test(&Solution::search, cases);

	return 0;
}