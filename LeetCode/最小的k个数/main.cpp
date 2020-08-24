// https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/

#include "../common/common.h"

// �ⷨ1�������ȡǰk����
class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    vector<int> solve()
    {
        sort(nums.begin(), nums.end());
        nums.resize(k);
        return nums;
    }

private:
    vector<int> nums;
    int k;
};

// �ⷨ2:k��ð������
class Solution2
{
public:
    Solution2(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    vector<int> solve()
    {
        for (int i = 0; i < (int)nums.size() - k; ++i)
        {
            for (int j = 0; j < (int)nums.size() - i - 1; ++j)
            {
                if (nums[j] > nums[j + 1])
                {
                    swap(nums[j], nums[j + 1]);
                }
            }
        }

        nums.resize(k);
        return nums;
    }

private:
    vector<int> nums;
    int k;
};

// �ⷨ3��C++��׼�⺯��nth_element
class Solution3
{
public:
    Solution3(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    vector<int> solve()
    {
        nth_element(nums.begin(), nums.begin() + k, nums.end());
        nums.resize(k);
        return nums;
    }

private:
    vector<int> nums;
    int k;
};

class Solution
{
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k)
    {
        //return Solution1(arr, k).solve();
        //return Solution2(arr, k).solve();
        return Solution3(arr, k).solve();
    }
};

int main()
{
	return 0;
}