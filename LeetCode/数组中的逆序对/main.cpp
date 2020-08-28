// https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        temp = vector<int>(nums.size());
        return mergeSort(0, nums.size() - 1);
    }

private:
    vector<int> nums;
    vector<int> temp;

    int mergeSort(int low, int high)
    {
        if (low >= high)
        {
            return 0;
        }

        int count = 0;
        int mid = (low + high) / 2;
        count += mergeSort(low, mid);
        count += mergeSort(mid + 1, high);

        int i = low, j = mid + 1;
        for (int k = low; k <= high; ++k)
        {
            if (i > mid)
            {
                temp[k] = nums[j++];
            }
            else if (j > high)
            {
                temp[k] = nums[i++];
            }
            else if (nums[i] <= nums[j])
            {
                temp[k] = nums[i++];
            }
            else
            {
                count += (mid - i + 1);
                temp[k] = nums[j++];
            }
        }

        for (int k = low; k <= high; ++k)
        {
            nums[k] = temp[k];
        }

        return count;
    }
};

class Solution
{
public:
    int reversePairs(vector<int>& nums)
    {
        return Solution1(nums).solve();
    }
};

int main()
{
    vector<int> input{ 7, 5, 6, 4 };
    assert(Solution().reversePairs(input) == 5);
    input = vector<int>{ 1, 3, 2, 3, 1 };
    assert(Solution().reversePairs(input) == 4);

	return 0;
}