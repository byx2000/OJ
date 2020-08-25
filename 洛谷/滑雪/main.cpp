// https://www.luogu.com.cn/problem/P1434

#include <iostream>
#include <vector>

using namespace std;

// �ⷨ1�����仯����
class Solution1
{
public:
	Solution1(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size()) {}

	int solve()
	{
		cache = vector<vector<int>>(row, vector<int>(col, -1));

		int res = 1;
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
		if (cache[r][c] != -1)
		{
			return cache[r][c];
		}

		static int d[4][2] =
		{
			-1, 0,
			1, 0,
			0, -1,
			0, 1,
		};

		int ret = 1;
		for (int i = 0; i < 4; ++i)
		{
			int nr = r + d[i][0];
			int nc = c + d[i][1];
			if (valid(nr, nc) && nums[r][c] > nums[nr][nc])
			{
				ret = max(ret, dp(nr, nc) + 1);
			}
		}

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