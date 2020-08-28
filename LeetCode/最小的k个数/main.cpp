// https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/

#include "../common/common.h"

// 解法1：排序后取前k个数
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

// 解法2:k趟冒泡排序
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

// 解法3：C++标准库函数nth_element
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

// 解法4：大根堆
class Solution4
{
public:
    Solution4(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    vector<int> solve()
    {
        if (k == 0)
        {
            return vector<int>();
        }

        priority_queue<int> pq(nums.begin(), nums.begin() + k);
        for (int i = k; i < (int)nums.size(); ++i)
        {
            if (nums[i] < pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }

        vector<int> res;
        while (!pq.empty())
        {
            res.push_back(pq.top());
            pq.pop();
        }

        return res;
    }

private:
    vector<int> nums;
    int k;
};

// 解法5：快速排序思想
class Solution5
{
public:
    Solution5(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    vector<int> solve()
    {
        select(0, nums.size() - 1, k);
        nums.resize(k);
        return nums;
    }

private:
    vector<int> nums;
    int k;

    void select(int low, int high, int n)
    {
        if (high - low + 1 <= n || low > high || n <= 0)
        {
            return;
        }

        // 划分

        int i = low + 1, j = high;
        while (1)
        {
            while (i < j && nums[i] <= nums[low]) i++;
            if (i == j) break;
            while (i < j && nums[j] > nums[low]) j--;
            if (i == j) break;
            swap(nums[i], nums[j]);
        }

        int mid = (nums[i] <= nums[low]) ? i : i - 1;
        swap(nums[low], nums[mid]);

        // 分治

        if (mid - low + 1 == n)
        {
            return;
        }
        else if (mid - low + 1 > n)
        {
            select(low, mid - 1, n);
        }
        else
        {
            select(mid + 1, high, n - (mid - low + 1));
        }
    }
};

class Solution
{
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k)
    {
        //return Solution1(arr, k).solve();
        //return Solution2(arr, k).solve();
        //return Solution3(arr, k).solve();
        //return Solution4(arr, k).solve();
        return Solution5(arr, k).solve();
    }
};

int main()
{
	return 0;
}