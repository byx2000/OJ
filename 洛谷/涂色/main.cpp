// https://www.luogu.com.cn/problem/P4170

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const string& s) : s(s) {}

	int solve()
	{
		cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
		return dp(0, s.size() - 1);
	}

private:
	string s;
	vector<vector<int>> cache;

	int dp(int i, int j)
	{
		if (cache[i][j] != -1)
		{
			return cache[i][j];
		}

		if (i == j)
		{
			return cache[i][j] = 1;
		}
		else if (s[i] == s[j])
		{
			return cache[i][j] = min(dp(i + 1, j), dp(i, j - 1));
		}
		else
		{
			int res = INT_MAX;
			for (int k = i; k < j; ++k)
			{
				res = min(res, dp(i, k) + dp(k + 1, j));
			}

			return cache[i][j] = res;
		}
	}
};

int main()
{
	string s;
	cin >> s;

	cout << Solution1(s).solve();
	
	return 0;
}