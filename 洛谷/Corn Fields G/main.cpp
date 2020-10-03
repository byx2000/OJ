// https://www.luogu.com.cn/problem/P1879

#include <iostream>
#include <vector>

using namespace std;

// 回溯法
class Solution1
{
public:
	Solution1(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size()) 
	{
		offset = vector<vector<int>>
		{
			{-1, 0},
			{1, 0},
			{0, -1},
			{0, 1},
		};
	}

	int solve()
	{
		cnt = 0;
		dfs(0);
		return (int)cnt;
	}

private:
	vector<vector<int>> nums;
	vector<vector<int>> offset;
	int row, col;
	long long cnt;
	const int MOD = 100000000;

	bool valid(int r, int c)
	{
		return r >= 0 && r < row && c >= 0 && c < col && nums[r][c] != 0;
	}

	bool canSet(int pos)
	{
		int r = pos / col;
		int c = pos % col;
		return valid(r, c) && nums[r][c] == 1;
	}

	void set(int pos)
	{
		int r = pos / col;
		int c = pos % col;
		nums[r][c]++;
		for (int i = 0; i < (int)offset.size(); ++i)
		{
			int nr = r + offset[i][0];
			int nc = c + offset[i][1];
			if (valid(nr, nc)) nums[nr][nc]++;
		}
	}

	void unset(int pos)
	{
		int r = pos / col;
		int c = pos % col;
		nums[r][c]--;
		for (int i = 0; i < (int)offset.size(); ++i)
		{
			int nr = r + offset[i][0];
			int nc = c + offset[i][1];
			if (valid(nr, nc)) nums[nr][nc]--;
		}
	}

	void dfs(int pos)
	{
		for (int p = pos; p < row * col; ++p)
		{
			if (canSet(p))
			{
				set(p);
				dfs(p + 1);
				unset(p);
			}
		}
		cnt = (cnt + 1) % MOD;
	}
};

// 状态压缩dp
class Solution2
{
public:
	Solution2(const vector<vector<int>>& nums)
		: nums(nums), row(nums.size()), col(nums[0].size())
	{
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			int sum = 0;
			for (int j = 0; j < (int)nums[i].size(); ++j)
			{
				sum = (sum << 1) + nums[i][j];
			}
			rows.push_back(sum);
		}
	}

	int solve()
	{
		cache = vector<vector<long long>>(row + 1, vector<long long>((1 << col), -1));
		return (int)dp(0, 0);
	}

private:
	vector<vector<int>> nums;
	int row, col;
	vector<int> rows;
	vector<vector<long long>> cache;
	const int MOD = 100000000;

	// r: 行数	s: 该行的状态
	// 判断是否有草种在贫瘠的土地上，以及是否有草相邻
	bool canSetAtRow(int r, int s)
	{
		return (rows[r] & s) == s && !(s & (s << 1)) && !(s & (s >> 1));
	}

	// 判断相邻两行是否有草相邻
	bool canSetAdjacent(int s1, int s2)
	{
		return !(s1 & s2);
	}

	// 当前处于第r行，上一行的状态为s
	long long dp(int r, int s)
	{
		if (cache[r][s] != -1) return cache[r][s];
		if (r == row) return cache[r][s] = 1;
		long long cnt = 0;
		for (int i = 0; i < (1 << col); ++i)
		{
			if (canSetAtRow(r, i) && canSetAdjacent(s, i))
			{
				cnt = (cnt + dp(r + 1, i)) % MOD;
			}
		}
		return cache[r][s] = cnt;
	}
};

int main()
{
	int row, col;
	cin >> row >> col;

	vector<vector<int>> nums(row, vector<int>(col));
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> nums[i][j];
		}
	}

	//cout << Solution1(nums).solve();
	cout << Solution2(nums).solve();

	return 0;
}