// https://www.luogu.com.cn/problem/P1352

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<vector<int>>& children, const vector<int>& values)
		: children(children), values(values) {}

	int solve()
	{
		cache = vector<vector<int>>(children.size(), vector<int>(2, -1));

		int res = 0;
		for (int i = 0; i < (int)children.size(); ++i)
		{
			res = max(res, dp(i, true));
			res = max(res, dp(i, false));
		}

		return res;
	}

private:
	vector<vector<int>> children;
	vector<int> values;
	vector<vector<int>> cache;

	int dp(int parent, bool choose)
	{
		if (cache[parent][choose] != -1)
		{
			return cache[parent][choose];
		}

		int ret = 0;

		if (choose)
		{
			for (int c : children[parent])
			{
				ret += dp(c, false);
			}
			ret += values[parent];
		}
		else
		{
			for (int c : children[parent])
			{
				ret += max(dp(c, true), dp(c, false));
			}
		}

		return cache[parent][choose] = ret;
	}
};

int main()
{
	int n;
	cin >> n;

	vector<int> values(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> values[i];
	}

	vector<vector<int>> children(n);
	for (int i = 0; i < n - 1; ++i)
	{
		int p, c;
		cin >> c >> p;
		children[p - 1].push_back(c - 1);
	}

	cout << Solution(children, values).solve();

	return 0;
}