// https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    vector<int> solve()
    {
        return { findFirst(), findLast() };
    }

private:
    vector<int> nums;
    int target;

    int findFirst()
    {
        int low = 0, high = nums.size() - 1;

        // ���ԣ���target��nums�У���target��һ�γ��ֵ��±�һ����[low, high]��
        while (high - low > 3)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target) high = mid;
            else if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        
        for (int i = low; i <= high; ++i) // ����Ҫ�ҵ�һ�γ��ֵ�λ�ã����Դ�����ɨ��
        {
            if (nums[i] == target) return i;
        }

        return -1;
    }

    int findLast()
    {
        int low = 0, high = nums.size() - 1;

        // ���ԣ���target��nums�У���target���һ�γ��ֵ��±�һ����[low, high]��
        while (high - low > 3)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target) low = mid; // ע����һ����findFirst()��ͬ
            else if (nums[mid] < target) low = mid + 1;
            else high = mid - 1;
        }

        for (int i = high; i >= low; --i) // ����Ҫ�����һ�γ��ֵ�λ�ã����Դ��ҵ���ɨ��
        {
            if (nums[i] == target) return i;
        }

        return -1;
    }
};

class Solution
{
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
        return Solution1(nums, target).solve();
    }
};

int main()
{
    Cases<vector<int>, int, vector<int>> cases
    {
        {{1}, 1, {0, 0}},
        {{1}, 2, {-1, -1}},
        {{1,2}, 1, {0,0}},
        {{1,2}, 2, {1,1}},
        {{1,2}, 3, {-1,-1}},
        {{5,7,7,8,8,10}, 8, {3,4}},
        {{5,7,7,8,8,10}, 6, {-1,-1}},
    };

    test(&Solution::searchRange, cases);

	return 0;
}