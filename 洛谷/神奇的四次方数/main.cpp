// https://www.luogu.com.cn/problem/P1679

#include <iostream>
#include <vector>

using namespace std;

// 完全背包 dp
class Solution1
{
public:
	Solution1(int m) : m(m) {}
	
	int solve()
	{
		cache = vector<vector<int>>(19, vector<int>(m + 1, -2));
		return dp(18, m);
	}

private:
	int m;
	vector<vector<int>> cache;

	// 将1~i个物品塞满空间为s的背包所需的最少物品数
	// 若无法正好塞满，则返回-1
	int dp(int i, int s)
	{
		if (s < 0)
		{
			return -1;
		}

		if (i == 0)
		{
			return (s == 0) ? 0 : -1;
		}

		if (cache[i][s] != -2)
		{
			return cache[i][s];
		}

		int r1 = dp(i - 1, s);
		int r2 = dp(i, s - i * i * i * i);

		if (r1 == -1 && r2 == -1)
		{
			return cache[i][s] = -1;
		}
		else if (r1 == -1)
		{
			return cache[i][s] = r2 + 1;
		}
		else if (r2 == -1)
		{
			return cache[i][s] = r1;
		}
		else
		{
			return cache[i][s] = min(r1, r2 + 1);
		}
	}
};

int main()
{
	int m;
	cin >> m;
	cout << Solution1(m).solve();

	return 0;
}