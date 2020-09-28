// https://www.luogu.com.cn/problem/P6218

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution1
{
public:
	Solution1(int n) : n(n) {}

	int solve()
	{
		if (n == 0) return 1;
		bin = toBin(n);
		cache = vector<vector<vector<vector<vector<int>>>>>(bin.size() + 1, vector<vector<vector<vector<int>>>>(bin.size() + 1, vector<vector<vector<int>>>(bin.size() + 1, vector<vector<int>>(2, vector<int>(2, -1)))));
		return dfs(0, 0, 0, true, true);
	}

private:
	int n;
	vector<int> bin;
	vector<vector<vector<vector<vector<int>>>>> cache;

	vector<int> toBin(int n)
	{
		vector<int> bin;
		while (n)
		{
			bin.push_back(n % 2);
			n /= 2;
		}
		reverse(bin.begin(), bin.end());
		return bin;
	}

	int dfs(int index, int c0, int c1, bool top, bool leading)
	{
		if (cache[index][c0][c1][top][leading] != -1) return cache[index][c0][c1][top][leading];

		if (index == bin.size()) return cache[index][c0][c1][top][leading] = (c0 >= c1) ? 1 : 0;

		int cnt = 0;
		int upper = top ? bin[index] : 1;
		for (int i = 0; i <= upper; ++i)
		{
			if (leading)
			{
				if (i == 0)
					cnt += dfs(index + 1, 0, c1, top && i == bin[index], true);
				else
					cnt += dfs(index + 1, 0, c1 + 1, top && i == bin[index], false);
			}
			else
			{
				if (i == 0)
					cnt += dfs(index + 1, c0 + 1, c1, top && i == bin[index], false);
				else
					cnt += dfs(index + 1, c0, c1 + 1, top && i == bin[index], false);
			}
		}

		return cache[index][c0][c1][top][leading] = cnt;
	}
};

int main()
{
	int a, b;
	cin >> a >> b;
	cout << Solution1(b).solve() - Solution1(a - 1).solve();

	return 0;
}