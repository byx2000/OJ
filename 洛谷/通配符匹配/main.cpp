// https://www.luogu.com.cn/problem/P3167

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const string& p, const string& s)
		: p(p), s(s) {}

	bool solve()
	{
		cache = vector<vector<bool>>(p.size(), vector<bool>(s.size()));
		book = vector<vector<bool>>(p.size(), vector<bool>(s.size(), false));
		return dp(0, 0);
	}

private:
	string p, s;
	vector<vector<bool>> cache;
	vector<vector<bool>> book;

	bool dp(int i, int j)
	{
		if (i == p.size())
		{
			return j == s.size();
		}

		if (j == s.size())
		{
			for (; i < (int)p.size(); ++i)
			{
				if (p[i] != '*')
				{
					return false;
				}
			}
			return true;
		}

		if (book[i][j])
		{
			return cache[i][j];
		}
		book[i][j] = true;

		if (p[i] == s[j] || p[i] == '?')
		{
			return cache[i][j] = dp(i + 1, j + 1);
		}
		else if (p[i] == '*')
		{
			return cache[i][j] = dp(i + 1, j) || dp(i, j + 1);
		}
		else
		{
			return cache[i][j] = false;
		}
	}
};

int main()
{
	string p;
	cin >> p;

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		cout << (Solution1(p, s).solve() ? "YES" : "NO") << endl;
	}

	return 0;
}