// https://www.luogu.com.cn/problem/P3146

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution
{
public:
	Solution(const vector<int>& nums) : nums(nums) {}

	int solve()
	{
		cache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

		int result = numeric_limits<int>::min();
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			for (int j = i; j < (int)nums.size(); ++j)
			{
				result = max(result, dp(i, j));
			}
		}

		return result;
	}

private:
	vector<int> nums;
	vector<vector<int>> cache;

	// 将nums[i]到nums[j]全部合并后能获得的最大值
	int dp(int i, int j)
	{
		if (cache[i][j] != -1)
		{
			return cache[i][j];
		}

		if (i == j)
		{
			return cache[i][j] = nums[i];
		}

		int ret = numeric_limits<int>::min();
		for (int k = i; k < j; ++k)
		{
			if (dp(i, k) == dp(k + 1, j))
			{
				ret = max(ret, dp(i, k) + 1);
			}
		}

		return cache[i][j] = ret;
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