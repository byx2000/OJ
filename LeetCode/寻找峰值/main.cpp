// https://leetcode-cn.com/problems/find-peak-element/

#include "../common/common.h"

// ���ַ�
class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        int left = 0, right = nums.size() - 1;

        // ÿ��ѭ����ʼʱ��left���ڵ�λ��Ϊ�����¡���right���ڵ�λ��Ϊ�����¡�
        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            // mid����λ��Ϊ�����¡���˵��mid��right֮��һ���С�ɽ�塱
            if (nums[mid] > nums[mid - 1]) left = mid;
            // ����˵��left��mid֮��һ���С�ɽ�塱
            else right = mid;
        }

        for (int i = left + 1; i <= right - 1; ++i)
        {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) return i;
        }

        return (nums[left] > nums[right]) ? left : right;
    }

private:
    vector<int> nums;
};

// ���ַ�
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    int solve()
    {
        int left = 0, right = nums.size() - 1;

        while (right - left > 3)
        {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;
            if (nums[mid1] < nums[mid2]) left = mid1;
            else right = mid2;
        }

        for (int i = left + 1; i <= right - 1; ++i)
        {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) return i;
        }

        return (nums[left] > nums[right]) ? left : right;
    }

private:
    vector<int> nums;
};

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    // �޲���

	return 0;
}