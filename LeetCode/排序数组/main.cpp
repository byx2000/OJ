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

// øÏÀŸ≈≈–Ú µ›πÈ
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

// øÏÀŸ≈≈–Ú ∑«µ›πÈ
class Solution3
{
public:
    Solution3(const vector<int>& nums) : nums(nums) {}

    vector<int> solve()
    {
        stack<Frame> callStack;
        callStack.push(Frame(0, nums.size() - 1));

        while (!callStack.empty())
        {
            Frame& cur = callStack.top();

            if (cur.s == 0)
            {
                if (cur.left >= cur.right) { callStack.pop(); continue; }
                cur.mid = partition(cur.left, cur.right);
                callStack.push(Frame(cur.left, cur.mid - 1));
                cur.s = 1;
            }
            else if (cur.s == 1)
            {
                callStack.pop();
                callStack.push(Frame(cur.mid + 1, cur.right));
            }
        }

        return nums;
    }

private:
    vector<int> nums;

    struct Frame
    {
        int left, right;
        int mid;
        int s;
        Frame(int left, int right)
            : left(left), right(right), s(0), mid(0) {}
    };

    int partition(int left, int right)
    {
        int mid = left;
        for (int i = left + 1; i <= right; ++i)
        {
            if (nums[i] > nums[left]) continue;
            swap(nums[mid + 1], nums[i]);
            mid++;
        }
        swap(nums[left], nums[mid]);
        return mid;
    }
};

class Solution
{
public:
    vector<int> sortArray(vector<int>& nums)
    {
        //return Solution1(nums).solve();
        //return Solution2(nums).solve();
        return Solution3(nums).solve();
    }
};

int main()
{	
    Cases<vector<int>, vector<int>> cases
    {
        {{5,2,3,1}, {1, 2, 3, 5}},
        {{5,1,1,2,0,0}, {0, 0, 1, 1, 2, 5}},
    };

    test(&Solution::sortArray, cases);

	return 0;
}