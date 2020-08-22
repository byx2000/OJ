// https://www.luogu.com.cn/problem/P1616

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 解法1：记忆化搜索（MLE、TLE）
class Solution1
{
public:
	Solution1(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		cache = vector<vector<int>>(weights.size(), vector<int>(space + 1, -1));
		return dp(weights.size() - 1, space);
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;
	vector<vector<int>> cache;

	int dp(int index, int leftSpace)
	{
		if (leftSpace <= 0)
		{
			return 0;
		}

		if (index == 0)
		{
			return leftSpace / weights[0] * values[0];
		}

		if (cache[index][leftSpace] != -1)
		{
			return cache[index][leftSpace];
		}

		int ret = dp(index - 1, leftSpace);
		if (leftSpace >= weights[index])
		{
			ret = max(ret, dp(index, leftSpace - weights[index]) + values[index]);
		}

		return cache[index][leftSpace] = ret;
	}
};

// 解法2：二维数组dp（MLE）
class Solution2
{
public:
	Solution2(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		vector<vector<int>> dp(weights.size(), vector<int>(space + 1, 0));

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			dp[0][leftSpace] = leftSpace / weights[0] * values[0];
		}

		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
			{
				dp[index][leftSpace] = dp[index - 1][leftSpace];
				if (leftSpace >= weights[index])
				{
					dp[index][leftSpace] = max(dp[index][leftSpace], dp[index][leftSpace - weights[index]] + values[index]);
				}
			}
		}

		return dp[weights.size() - 1][space];
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;
};

// 解法3：一维数组dp（AC）
class Solution3
{
public:
	Solution3(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		vector<int> dp(space + 1, 0);

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			dp[leftSpace] = leftSpace / weights[0] * values[0];
		}

		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
			{
				if (leftSpace >= weights[index])
				{
					dp[leftSpace] = max(dp[leftSpace], dp[leftSpace - weights[index]] + values[index]);
				}
			}
		}

		return dp[space];
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;
};

int main()
{
	int cnt, space;
	cin >> space >> cnt;

	vector<int> weights;
	vector<int> values;

	for (int i = 0; i < cnt; ++i)
	{
		int weight, value;
		cin >> weight >> value;
		weights.push_back(weight);
		values.push_back(value);
	}

	//cout << Solution1(weights, values, space).solve();
	//cout << Solution2(weights, values, space).solve();
	cout << Solution3(weights, values, space).solve();

	return 0;
}