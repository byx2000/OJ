// https://www.luogu.com.cn/problem/P1880

#include <iostream>
#include <vector>
#include <climits>
#include <map>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const vector<int>& nums) : nums(nums) 
	{
		int n = nums.size();
		for (int i = 0; i < n; ++i)
		{
			this->nums.push_back(nums[i]);
		}
	}

	pair<int, int> solve()
	{
		int minVal = INT_MAX, maxVal = -1;

		minCache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));
		maxCache = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

		for (int i = 0; i < (int)nums.size() / 2; ++i)
		{
			minVal = min(minVal, dpMin(i, i + nums.size() / 2 - 1));
			maxVal = max(maxVal, dpMax(i, i + nums.size() / 2 - 1));
		}

		return pair<int, int>(minVal, maxVal);
	}

private:
	vector<int> nums;
	vector<vector<int>> minCache;
	vector<vector<int>> maxCache;

	int dpMin(int i, int j)
	{
		if (minCache[i][j] != -1)
		{
			return minCache[i][j];
		}

		if (i == j)
		{
			return minCache[i][j] = 0;
		}
		else if (i + 1 == j)
		{
			return minCache[i][j] = nums[i] + nums[j];
		}
		else
		{
			int ret = INT_MAX;
			for (int k = i; k < j; ++k)
			{
				ret = min(ret, dpMin(i, k) + dpMin(k + 1, j));
			}

			for (int k = i; k <= j; ++k)
			{
				ret += nums[k];
			}

			return minCache[i][j] = ret;
		}
	}

	int dpMax(int i, int j)
	{
		if (maxCache[i][j] != -1)
		{
			return maxCache[i][j];
		}

		if (i == j)
		{
			return maxCache[i][j] = 0;
		}
		else if (i + 1 == j)
		{
			return maxCache[i][j] = nums[i] + nums[j];
		}
		else
		{
			int ret = -1;
			for (int k = i; k < j; ++k)
			{
				ret = max(ret, dpMax(i, k) + dpMax(k + 1, j));
			}

			for (int k = i; k <= j; ++k)
			{
				ret += nums[k];
			}

			return maxCache[i][j] = ret;
		}
	}
};

// 解法2：二维数组dp
class Solution2
{
public:
	Solution2(const vector<int>& nums) : nums(nums)
	{
		int n = nums.size();
		for (int i = 0; i < n; ++i)
		{
			this->nums.push_back(nums[i]);
		}
	}

	pair<int, int> solve()
	{
		int n = nums.size();

		// 计算最小值

		vector<vector<int>> dpMin(n, vector<int>(n, 0));

		for (int i = 0; i < n; ++i)
		{
			dpMin[i][i] = 0;
		}

		for (int i = 0; i < n - 1; ++i)
		{
			dpMin[i][i + 1] = nums[i] + nums[i + 1];
		}

		for (int a = 0; a < n - 2; ++a)
		{
			for (int j = a + 2; j < n; ++j)
			{
				int i = j - (a + 2);
				dpMin[i][j] = INT_MAX;
				for (int k = i; k < j; ++k)
				{
					dpMin[i][j] = min(dpMin[i][j], dpMin[i][k] + dpMin[k + 1][j]);
				}
				for (int k = i; k <= j; ++k)
				{
					dpMin[i][j] += nums[k];
				}
			}
		}

		int minVal = INT_MAX;
		for (int i = 0; i < n / 2; ++i)
		{
			minVal = min(minVal, dpMin[i][i + n / 2 - 1]);
		}

		// 计算最大值

		vector<vector<int>> dpMax(n, vector<int>(n, 0));

		for (int i = 0; i < n; ++i)
		{
			dpMax[i][i] = 0;
		}

		for (int i = 0; i < n - 1; ++i)
		{
			dpMax[i][i + 1] = nums[i] + nums[i + 1];
		}

		for (int a = 0; a < n - 2; ++a)
		{
			for (int j = a + 2; j < n; ++j)
			{
				int i = j - (a + 2);
				dpMax[i][j] = -1;
				for (int k = i; k < j; ++k)
				{
					dpMax[i][j] = max(dpMax[i][j], dpMax[i][k] + dpMax[k + 1][j]);
				}
				for (int k = i; k <= j; ++k)
				{
					dpMax[i][j] += nums[k];
				}
			}
		}

		int maxVal = -1;
		for (int i = 0; i < n / 2; ++i)
		{
			maxVal = max(maxVal, dpMax[i][i + n / 2 - 1]);
		}

		return pair<int, int>(minVal, maxVal);
	}

private:
	vector<int> nums;
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

	//pair<int, int> res = Solution1(nums).solve();
	pair<int, int> res = Solution2(nums).solve();

	cout << res.first << endl;
	cout << res.second << endl;

	return 0;
}