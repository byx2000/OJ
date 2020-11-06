// https://leetcode-cn.com/problems/binary-search/

#include "../common/common.h"

// �ⷨ1��lower_bound�⺯��
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

// �ⷨ2�����ֲ���
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

// �ⷨ3�����ܷ���
class Solution3
{
public:
    Solution3(const vector<int>& nums, int target)
        : nums(nums), target(target) {}

    int solve()
    {
        int low = 0, high = nums.size() - 1;
        while (high - low > 3) // �����䳤��С��3ʱ���˳�ѭ������ֹ�����䳤�ȹ�Сʱ������ѭ��
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                low = mid; // ��ʹ�˴��ı߽������������ܷ�����ȷ���
            }
            else
            {
                high = mid;
            }
        }

        for (int i = low; i <= high; ++i)
        {
            if (nums[i] == target) return i;
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
        //return Solution2(nums, target).solve();
        return Solution3(nums, target).solve();
    }
};

int main()
{
    Cases<vector<int>, int, int> cases
    {
        {{}, 1, -1},
        {{1}, 1, 0},
        {{1}, 2, -1},
        {{1,2}, 1, 0},
        {{1,2}, 2, 1},
        {{1,2}, 3, -1},
        {{-1,0,3,5,9,12}, 9, 4},
        {{-1,0,3,5,9,12}, 2, -1},
    };

    test(&Solution::search, cases);

	return 0;
}