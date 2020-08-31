// https://leetcode-cn.com/problems/binary-search/

#include "../common/common.h"

// 解法1：lower_bound库函数
class Solution1
{
public:
    Solution1(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), target);
        int index = distance(nums.begin(), it);
        bool find = index >= 0 && index < (int)nums.size() && nums[index] == target;
        return find ? index : -1;
    }

private:
    vector<int> nums;
    int target;
};

// 解法2：二分查找
class Solution2
{
public:
    Solution2(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        int low = 0, high = nums.size() - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
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
        //return Solution1(nums, target).solve();
        return Solution2(nums, target).solve();
    }
};

int main()
{
	return 0;
}