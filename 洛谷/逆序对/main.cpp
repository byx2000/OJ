// https://www.luogu.com.cn/problem/P1908

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    Solution(const vector<int>& nums) : nums(nums) {}

    long long solve()
    {
        temp = vector<int>(nums.size());
        return mergeSort(0, nums.size() - 1);
    }

private:
    vector<int> nums;
    vector<int> temp;

    long long mergeSort(int low, int high)
    {
        if (low >= high)
        {
            return 0;
        }

        long long count = 0;
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
                count += ((long long)mid - i + 1);
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

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    cout << Solution(nums).solve();

	return 0;
}