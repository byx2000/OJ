// https://www.luogu.com.cn/problem/P1287

#include <iostream>

using namespace std;

class Solution
{
public:
	Solution(int n, int r) : n(n), r(r) {}

	int solve()
	{
		return dp(n, r);
	}

private:
	int n, r;

	int dp(int n, int r)
	{
		if (r == 1)
		{
			return 1;
		}

		if (n < r)
		{
			return 0;
		}

		return r * (dp(n - 1, r - 1) + dp(n - 1, r));
	}
};

int main()
{
	int n, r;
	cin >> n >> r;

	cout << Solution(n, r).solve();

	return 0;
}