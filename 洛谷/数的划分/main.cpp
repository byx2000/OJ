// https://www.luogu.com.cn/problem/P1025

#include <iostream>
#include <vector>

using namespace std;

// 解法1：DFS
class Solution1
{
public:
	Solution1(int n, int k)
		: n(n), k(k), count(0) {}

	int solve()
	{
		count = 0;
		dfs(1, 0, 0);
		return count;
	}

private:
	int n, k;
	int count;

	void dfs(int last, int sum, int step)
	{
		if (step == k)
		{
			if (sum == n)
			{
				count++;
			}
			return;
		}

		for (int i = last; sum + (k - step) * i <= n; ++i)
		{
			dfs(i, sum + i, step + 1);
		}
	}
};

// 解法2：动态规划
class Solution2
{
public:
	Solution2(int n, int k) : n(n), k(k) {}

	int solve()
	{
		cache = vector<vector<int>>(n + 1, vector<int>(k + 1, -1));
		return dp(n, k);
	}

private:
	int n, k;
	vector<vector<int>> cache;

	int dp(int n, int k)
	{
		if (k == 1)
		{
			return 1;
		}

		if (n < k)
		{
			return 0;
		}

		if (cache[n][k] != -1)
		{
			return cache[n][k];
		}

		return cache[n][k] = dp(n - 1, k - 1) + dp(n - k, k);
	}
};

int main()
{
	int n, k;
	cin >> n >> k;

	//cout << Solution1(n, k).solve();
	cout << Solution2(n, k).solve();

	return 0;
}