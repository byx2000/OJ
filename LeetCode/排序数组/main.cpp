// https://leetcode-cn.com/problems/sort-an-array/

#include "../common/common.h"

// πÈ≤¢≈≈–Ú
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    vector<int> solve()
    {
        temp = vector<int>(nums.size());
        mergeSort(0, nums.size() - 1);
        return nums;
    }

private:
    vector<int> nums;
    vector<int> temp;

    void mergeSort(int low, int high)
    {
        if (low >= high)
        {
            return;
        }

        int mid = (low + high) / 2;
        mergeSort(low, mid);
        mergeSort(mid + 1, high);

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
            else if (nums[i] < nums[j])
            {
                temp[k] = nums[i++];
            }
            else
            {
                temp[k] = nums[j++];
            }
        }

        for (int k = low; k <= high; ++k)
        {
            nums[k] = temp[k];
        }
    }
};

// øÏÀŸ≈≈–Ú
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    vector<int> solve()
    {
        quickSort(0, nums.size() - 1);
        return nums;
    }

private:
    vector<int> nums;

    void quickSort(int low, int high)
    {
        if (low >= high)
        {
            return;
        }

        int i = low + 1, j = high;
        while (1)
        {
            while (i < j && nums[i] <= nums[low]) i++;
            if (i == j) break;
            while (i < j && nums[j] > nums[low]) j--;
            if (i == j) break;
            swap(nums[i], nums[j]);
        }

        int k = (nums[i] <= nums[low]) ? i : i - 1;
        swap(nums[low], nums[k]);

        quickSort(low, k - 1);
        quickSort(k + 1, high);
    }
};

class Solution
{
public:
    vector<int> sortArray(vector<int>& nums)
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{	
    vector<int> nums{ 5,2,3,1 };
    TEST(Assert::areEqual(Solution().sortArray(nums), vector<int>{1, 2, 3, 5}));

    nums = vector<int>{ 5,1,1,2,0,0 };
    TEST(Assert::areEqual(Solution().sortArray(nums), vector<int>{0, 0, 1, 1, 2, 5}));

	return 0;
}