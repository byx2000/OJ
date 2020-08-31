// https://leetcode-cn.com/problems/majority-element/

#include "../common/common.h"

// 解法1：分治法
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        return search(0, nums.size() - 1);
    }

private:
    vector<int> nums;

    int search(int low, int high)
    {
        if (low == high)
        {
            return nums[low];
        }

        int mid = (low + high) / 2;
        int n1 = search(low, mid);
        int n2 = search(mid + 1, high);

        if (n1 == n2)
        {
            return n1;
        }

        int cnt = count(nums.begin() + low, nums.begin() + high + 1, n1);

        return (cnt > (high - low + 1) / 2) ? n1 : n2;
    }
};

class Solution
{
public:
    int majorityElement(vector<int>& nums)
    {
        return Solution1(nums).solve();
    }
};

int main()
{
	return 0;
}