// https://www.luogu.com.cn/problem/P1164

#include <iostream>
#include <vector>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(int space, const vector<int>& weights)
		: space(space), weights(weights) {}

	int solve()
	{
		cache = vector<vector<int>>(weights.size(), vector<int>(space + 1, -1));
		return dp(weights.size() - 1, space);
	}

private:
	int space;
	vector<int> weights;
	vector<vector<int>> cache;

	int dp(int index, int leftSpace)
	{
		if (leftSpace == 0)
		{
			return 1;
		}

		if (leftSpace < 0)
		{
			return 0;
		}

		if (index < 0)
		{
			return 0;
		}

		if (cache[index][leftSpace] != -1)
		{
			return cache[index][leftSpace];
		}

		int ret = dp(index - 1, leftSpace);
		if (leftSpace >= weights[index])
		{
			ret += dp(index - 1, leftSpace - weights[index]);
		}

		return cache[index][leftSpace] = ret;
	}
};

// 解法2：二维数组dp
class Solution2
{
public:
	Solution2(int space, const vector<int>& weights)
		: space(space), weights(weights) {}

	int solve()
	{
		vector<vector<int>> dp(weights.size(), vector<int>(space + 1, 0));

		dp[0][0] = 1;
		if (weights[0] <= space)
		{
			dp[0][weights[0]] = 1;
		}

		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
			{
				dp[index][leftSpace] = dp[index - 1][leftSpace];
				if (leftSpace >= weights[index])
				{
					dp[index][leftSpace] += dp[index - 1][leftSpace - weights[index]];
				}
			}
		}

		return dp[weights.size() - 1][space];
	}

private:
	int space;
	vector<int> weights;
};

// 解法3：一维数组dp
class Solution3
{
public:
	Solution3(int space, const vector<int>& weights)
		: space(space), weights(weights) {}

	int solve()
	{
		vector<int> dp(space + 1, 0);

		dp[0] = 1;
		if (weights[0] <= space)
		{
			dp[weights[0]] = 1;
		}
		
		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = space; leftSpace >= 0; --leftSpace)
			{
				if (leftSpace >= weights[index])
				{
					dp[leftSpace] += dp[leftSpace - weights[index]];
				}
			}
		}

		return dp[space];
	}

private:
	int space;
	vector<int> weights;
};

int main()
{
	int count, space;
	cin >> count >> space;

	vector<int> weights(count);
	for (int i = 0; i < count; ++i)
	{
		cin >> weights[i];
	}

	//cout << Solution1(space, weights).solve();
	//cout << Solution2(space, weights).solve();
	cout << Solution3(space, weights).solve();

	return 0;
}