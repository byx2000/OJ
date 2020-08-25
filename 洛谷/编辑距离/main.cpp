// https://www.luogu.com.cn/problem/P2758

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const string& s1, const string& s2)
		: s1(s1), s2(s2) {}

	int solve()
	{
		cache = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));
		return dp(s1.size() - 1, s2.size() - 1);
	}

private:
	string s1, s2;
	vector<vector<int>> cache;

	int dp(int i, int j)
	{
		if (i < 0)
		{
			return j + 1;
		}

		if (j < 0)
		{
			return i + 1;
		}

		if (cache[i][j] != -1)
		{
			return cache[i][j];
		}

		if (s1[i] == s2[j])
		{
			return cache[i][j] = dp(i - 1, j - 1);
		}
		else
		{
			int ret = dp(i - 1, j - 1) + 1;
			ret = min(ret, dp(i - 1, j) + 1);
			ret = min(ret, dp(i, j - 1) + 1);
			return cache[i][j] = ret;
		}
	}
};

int main()
{
	string s1, s2;
	cin >> s1 >> s2;

	cout << Solution1(s1, s2).solve();

	return 0;
}