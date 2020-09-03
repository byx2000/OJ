// https://www.luogu.com.cn/problem/P4302

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const string& s) : s(s) {}

	int solve()
	{
		cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
		return dp(0, s.size() - 1);
	}

private:
	string s;
	vector<vector<int>> cache;

	// 检查s[i]~s[j]是否能够由s[i]~s[k]折叠
	bool check(int i, int k, int j)
	{
		int len = k - i + 1;
		if ((j - i + 1) % len != 0)
		{
			return false;
		}

		for (int index = k + 1; index <= j; ++index)
		{
			int r = (index - k - 1) % len;
			if (s[i + r] != s[index])
			{
				return false;
			}
		}

		return true;
	}

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

		int ret = j - i + 1;
		for (int k = i; k < j; ++k)
		{
			ret = min(ret, dp(i, k) + dp(k + 1, j));
			if (check(i, k, j))
			{
				ret = min(ret, dp(i, k) + (int)to_string((j - i + 1) / (k - i + 1)).size() + 2);
			}
		}

		return cache[i][j] = ret;
	}
};

int main()
{
	string s;
	cin >> s;

	cout << Solution(s).solve();

	return 0;
}