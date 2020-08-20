// https://www.luogu.com.cn/problem/P1439

#include <iostream>
#include <vector>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const vector<int>& s1, const vector<int>& s2)
		: s1(s1), s2(s2) {}

	int solve()
	{
		cache = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));
		return dp(s1.size() - 1, s2.size() - 1);
	}

private:
	vector<int> s1, s2;
	vector<vector<int>> cache;

	int dp(int i, int j)
	{
		if (i < 0 || j < 0)
		{
			return 0;
		}

		if (cache[i][j] != -1)
		{
			return cache[i][j];
		}

		if (s1[i] == s2[j])
		{
			return cache[i][j] = dp(i - 1, j - 1) + 1;
		}
		else
		{
			return cache[i][j] = max(dp(i, j - 1), dp(i - 1, j));
		}
	}
};

// 解法2：二维数组dp
class Solution2
{
public:
	Solution2(const vector<int>& s1, const vector<int>& s2)
		: s1(s1), s2(s2) {}

	int solve()
	{
		vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), 0));

		dp[0][0] = (s1[0] == s2[0]) ? 1 : 0;
		for (int j = 1; j < (int)s2.size(); ++j)
		{
			dp[0][j] = (dp[0][j - 1] == 1 || s1[0] == s2[j]) ? 1 : 0;
		}

		for (int i = 1; i < (int)s1.size(); ++i)
		{
			dp[i][0] = (dp[i - 1][0] == 1 || s1[i] == s2[0]) ? 1 : 0;
		}

		for (int i = 1; i < (int)s1.size(); ++i)
		{
			for (int j = 1; j < (int)s2.size(); ++j)
			{
				if (s1[i] == s2[j])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else
				{
					dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
				}
			}
		}

		return dp[s1.size() - 1][s2.size() - 1];
	}

private:
	vector<int> s1, s2;
};

int main()
{
	int n;
	cin >> n;

	vector<int> s1(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> s1[i];
	}

	vector<int> s2(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> s2[i];
	}

	//cout << Solution1(s1, s2).solve();
	cout << Solution2(s1, s2).solve();

	return 0;
}