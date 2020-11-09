// https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/

#include "../common/common.h"

// ���ֲ���
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

// �⺯��
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