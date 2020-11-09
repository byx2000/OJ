// https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/

#include "../common/common.h"

// 二分查找
class Solution1
{
public:
    Solution1(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        int low = findFirst();
        if (low == -1) return 0;
        int high = findLast();
        return high - low + 1;
    }

private:
    vector<int> nums;
    int target;

    int findFirst()
    {
        int low = 0, high = nums.size() - 1;

        // 断言：若target在nums中，则target第一次出现的下标一定在[low, high]中
        while (high - low > 3)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target) high = mid;
            else if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }

        for (int i = low; i <= high; ++i) // 由于要找第一次出现的位置，所以从左到右扫描
        {
            if (nums[i] == target) return i;
        }

        return -1;
    }

    int findLast()
    {
        int low = 0, high = nums.size() - 1;

        // 断言：若target在nums中，则target最后一次出现的下标一定在[low, high]中
        while (high - low > 3)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target) low = mid; // 注意这一行与findFirst()不同
            else if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }

        for (int i = high; i >= low; --i) // 由于要找最后一次出现的位置，所以从右到左扫描
        {
            if (nums[i] == target) return i;
        }

        return -1;
    }
};

// 库函数
class Solution2
{
public:
    Solution2(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        vector<int>::iterator low = lower_bound(nums.begin(), nums.end(), target);
        if (low == nums.end()) return 0;
        vector<int>::iterator high = upper_bound(nums.begin(), nums.end(), target);
        return distance(low, high);
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
    Cases<vector<int>, int, int> cases
    {
        {{}, 0, 0},
        {{5,7,7,8,8,10}, 8, 2},
        {{5,7,7,8,8,10}, 6, 0},
    };

    test(&Solution::search, cases);

    return 0;
}