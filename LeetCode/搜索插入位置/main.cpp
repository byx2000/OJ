// https://leetcode-cn.com/problems/search-insert-position/

#include "../common/common.h"

class Solution 
{
public:
    int searchInsert(vector<int>& nums, int target)
    {
        int low = 0, high = nums.size() - 1;
        while (high - low > 3)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }

        for (int i = low; i <= high; ++i)
        {
            if (nums[i] >= target) return i;
        }

        return high + 1;
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{1,3,5,6}, 5, 2},
        {{1,3,5,6}, 2, 1},
        {{1,3,5,6}, 7, 4},
        {{1,3,5,6}, 0, 0},
    };

    test(&Solution::searchInsert, cases);

	return 0;
}