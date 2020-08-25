// https://www.luogu.com.cn/problem/P1004

#include <iostream>
#include <vector>

using namespace std;

// 解法1：四维dp
class Solution1
{
public:
	Solution1(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size()) {}

	int solve()
	{
		cache = vector<vector<vector<vector<int>>>>(row, vector<vector<vector<int>>>(col, vector<vector<int>>(row, vector<int>(col, -1))));
		return dp(row - 1, col - 1, row - 1, col - 1);
	}

private:
	vector<vector<int>> nums;
	int row, col;
	vector<vector<vector<vector<int>>>> cache; // 四维数组

	bool valid(int i, int j, int k, int l)
	{
		return i >= 0 && i < row&&
			j >= 0 && j < col&&
			k >= 0 && k < row&&
			l >= 0 && l < col;
	}

	int dp(int i, int j, int k, int l)
	{
		if (!valid(i, j, k, l))
		{
			return 0;
		}

		if (cache[i][j][k][l] != -1)
		{
			return cache[i][j][k][l];
		}

		int ret = dp(i - 1, j, k - 1, l);
		ret = max(ret, dp(i, j - 1, k - 1, l));
		ret = max(ret, dp(i - 1, j, k, l - 1));
		ret = max(ret, dp(i, j - 1, k, l - 1));
		if (i == k && j == l)
		{
			ret += nums[i][j];
		}
		else
		{
			ret += nums[i][j] + nums[k][l];
		}

		return cache[i][j][k][l] = ret;
	}
};

// 解法2：三维dp
class Solution2
{
public:
	Solution2(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size()) {}

	int solve()
	{
		cache = vector<vector<vector<int>>>(row + col, vector<vector<int>>(row, vector<int>(col, -1)));
		return dp(row + col - 1, row - 1, col - 1);
	}

private:
	vector<vector<int>> nums;
	int row, col;
	vector<vector<vector<int>>> cache; // 三维数组

	bool valid(int i, int j, int k, int l)
	{
		return i >= 0 && i < row&&
			j >= 0 && j < col&&
			k >= 0 && k < row&&
			l >= 0 && l < col;
	}

	int dp(int len, int i, int k)
	{
		int j = len - i - 1;
		int l = len - k - 1;

		if (!valid(i, j, k, l))
		{
			return 0;
		}

		if (cache[len][i][k] != -1)
		{
			return cache[len][i][k];
		}

		int ret = dp(len - 1, i, k);
		ret = max(ret, dp(len - 1, i - 1, k));
		ret = max(ret, dp(len - 1, i, k - 1));
		ret = max(ret, dp(len - 1, i - 1, k - 1));
		if (i == k)
		{
			ret += nums[i][j];
		}
		else
		{
			ret += nums[i][j] + nums[k][l];
		}

		return cache[len][i][k] = ret;
	}
};

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> nums(n, vector<int>(n, 0));
	int r, c, val;
	cin >> r >> c >> val;
	while (r != 0)
	{
		nums[r - 1][c - 1] = val;
		cin >> r >> c >> val;
	}

	//cout << Solution1(nums).solve();
	cout << Solution2(nums).solve();

	return 0;
}