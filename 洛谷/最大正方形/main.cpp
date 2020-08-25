// https://www.luogu.com.cn/problem/P1387

#include <iostream>
#include <vector>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size()) {}

	int solve()
	{
		cache = vector<vector<int>>(row, vector<int>(col, -1));

		int res = -1;
		for (int r = 0; r < row; ++r)
		{
			for (int c = 0; c < col; ++c)
			{
				res = max(res, dp(r, c));
			}
		}

		return res;
	}

private:
	vector<vector<int>> nums;
	int row, col;
	vector<vector<int>> cache;

	bool valid(int r, int c)
	{
		return r >= 0 && r < row&& c >= 0 && c < col;
	}

	int dp(int r, int c)
	{
		if (!valid(r, c))
		{
			return 0;
		}

		if (cache[r][c] != -1)
		{
			return cache[r][c];
		}

		if (nums[r][c] == 0)
		{
			return cache[r][c] = 0;
		}

		int ret = dp(r - 1, c);
		ret = min(ret, dp(r, c - 1));
		ret = min(ret, dp(r - 1, c - 1));
		ret++;

		return cache[r][c] = ret;
	}
};

int main()
{
	int row, col;
	cin >> row >> col;

	vector<vector<int>> nums(row, vector<int>(col));
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			cin >> nums[r][c];
		}
	}

	cout << Solution1(nums).solve();

	return 0;
}