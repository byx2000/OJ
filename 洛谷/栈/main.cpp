// https://www.luogu.com.cn/problem/P1044

#include <iostream>
#include <vector>

using namespace std;

// 记忆化搜索
// 本题等价于求n对括号的合法括号序列数
// https://leetcode-cn.com/problems/bracket-lcci/
class Solution
{
public:
	Solution(int n) : n(n) {}

	int solve()
	{
		cache = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
		return dfs(0, 0);
	}

private:
	int n;
	vector<vector<int>> cache;

	int dfs(int nPush, int nPop)
	{
		if (nPush == n && nPop == n)
		{
			return 1;
		}

		if (nPush > n || nPop > n || nPush < nPop)
		{
			return 0;
		}

		if (cache[nPush][nPop] != -1)
		{
			return cache[nPush][nPop];
		}

		return cache[nPush][nPop] = dfs(nPush + 1, nPop) + dfs(nPush, nPop + 1);
	}
};

int main()
{
	int n;
	cin >> n;

	cout << Solution(n).solve();

	return 0;
}