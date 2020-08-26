// https://www.luogu.com.cn/problem/P2014

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<vector<int>>& children, const vector<int>& values, int nChoose)
		: children(children), values(values), nChoose(nChoose) {}

	int solve()
	{
		int maxChildrenCount = 0;
		for (int i = 0; i < (int)children.size(); ++i)
		{
			maxChildrenCount = max(maxChildrenCount, (int)children[i].size());
		}

		cache = vector<vector<vector<int>>>(children.size() + 1, vector<vector<int>>(maxChildrenCount, vector<int>(nChoose + 2, -1)));

		return dp(0, children[0].size() - 1, nChoose + 1);
	}

private:
	vector<vector<int>> children;
	vector<int> values;
	int nChoose;
	vector<vector<vector<int>>> cache;

	int dp(int root, int iChild, int leftChoose)
	{
		if (leftChoose == 1)
		{
			return values[root];
		}

		if (children[root].size() == 0)
		{
			return values[root];
		}

		if (cache[root][iChild][leftChoose] != -1)
		{
			return cache[root][iChild][leftChoose];
		}

		int c = children[root][iChild];
		int nc = children[c].size();

		if (iChild == 0)
		{
			return cache[root][iChild][leftChoose] = values[root] + dp(c, nc - 1, leftChoose - 1);
		}

		int ret = dp(root, iChild - 1, leftChoose);
		
		for (int i = 1; i <= leftChoose - 1; ++i)
		{
			ret = max(ret, dp(c, nc - 1, i) + dp(root, iChild - 1, leftChoose - i));
		}

		ret = max(ret, dp(c, nc - 1, leftChoose - 1) + values[root]);

		return cache[root][iChild][leftChoose] = ret;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<int>> children(n + 1);
	vector<int> values(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		int p, v;
		cin >> p >> v;
		children[p].push_back(i);
		values[i] = v;
	}
	values[0] = 0;

	cout << Solution(children, values, m).solve();

	return 0;
}