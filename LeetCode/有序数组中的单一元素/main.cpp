// https://leetcode-cn.com/problems/single-element-in-a-sorted-array/

#include "../common/common.h"

// 解法1：O(n)
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        int i = 0;
        for (int v : nums)
        {
            i ^= v;
        }
        return i;
    }

private:
    vector<int> nums;
};

// 解法2：O(logn)
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        int left = 0, right = nums.size() - 1;

        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == nums[mid - 1])
            {
                if ((mid - 2 - left) % 2 == 0) right = mid - 2;
                else left = mid + 1;
            }
            else if (nums[mid] == nums[mid + 1])
            {
                if ((mid - 1 - left) % 2 == 0) right = mid - 1;
                else left = mid + 2;
            }
            else return nums[mid];
        }

        for (int i = left; i < right; i += 2)
        {
            if (nums[i] != nums[i + 1]) return nums[i];
        }

        return nums[right];
    }

private:
    vector<int> nums;
};

class Solution 
{
public:
    int singleNonDuplicate(vector<int>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{1,1,2,3,3,4,4,8,8}, 2},
        {{3,3,7,7,10,11,11}, 10},
    };

    test(&Solution::singleNonDuplicate, cases);

	return 0;
}