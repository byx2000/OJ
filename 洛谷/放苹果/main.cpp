// https://www.luogu.com.cn/problem/P2386

#include <iostream>

using namespace std;

class Solution
{
public:
	Solution(int n, int m) : n(n), m(m) {}

	int solve()
	{
		return dp(n, m);
	}

private:
	int n, m;

	int dp(int n, int m)
	{
		if (n < 0)
		{
			return 0;
		}

		if (n == 0 || m == 1)
		{
			return 1;
		}

		return dp(n, m - 1) + dp(n - m, m);
	}
};

int main()
{
	int t;
	cin >> t;

	while (t--)
	{
		int n, m;
		cin >> n >> m;
		cout << Solution(n, m).solve() << endl;
	}

	return 0;
}