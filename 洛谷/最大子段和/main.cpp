// https://www.luogu.com.cn/problem/P1115

#include <iostream>
#include <vector>

using namespace std;

// 解法1：动态规划 O(n)
class Solution1
{
public:
	Solution1(const vector<int>& nums) : nums(nums) {}

	int solve()
	{
		int dp = nums[0];
		int res = dp;
		for (int i = 1; i < (int)nums.size(); ++i)
		{
			dp = max(dp + nums[i], nums[i]);
			res = max(res, dp);
		}

		return res;
	}

private:
	vector<int> nums;
};

// 解法2：分治法 O(nlogn)
class Solution2
{
public:
	Solution2(const vector<int>& nums) : nums(nums) {}

	int solve()
	{
		return find(0, nums.size() - 1);
	}

private:
	vector<int> nums;

	int find(int low, int high)
	{
		if (low > high)
		{
			return 0;
		}

		if (low == high)
		{
			return nums[low];
		}

		int mid = (low + high) / 2;
		int ret = find(low, mid);
		ret = max(ret, find(mid + 1, high));

		int s1 = nums[mid];
		int m1 = s1;
		for (int i = mid - 1; i >= 0; --i)
		{
			s1 += nums[i];
			m1 = max(m1, s1);
		}

		int s2 = nums[mid + 1];
		int m2 = s2;
		for (int i = mid + 2; i <= high; ++i)
		{
			s2 += nums[i];
			m2 = max(m2, s2);
		}

		ret = max(ret, m1 + m2);

		return ret;
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

	//cout << Solution1(nums).solve();
	cout << Solution2(nums).solve();

	return 0;
}