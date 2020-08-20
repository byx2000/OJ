// https://www.luogu.com.cn/problem/P1048

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		cache.clear();
		return dp(weights.size() - 1, space);
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;
	map<pair<int, int>, int> cache;

	int dp(int index, int leftSpace)
	{
		pair<int, int> key(index, leftSpace);

		if (cache.count(key) > 0)
		{
			return cache[key];
		}

		if (leftSpace <= 0)
		{
			return cache[key] = 0;
		}

		if (index == 0)
		{
			if (leftSpace >= weights[0])
			{
				return cache[key] = values[0];
			}
			else
			{
				return cache[key] = 0;
			}
		}

		int ret = dp(index - 1, leftSpace);
		if (leftSpace >= weights[index])
		{
			ret = max(ret, dp(index - 1, leftSpace - weights[index]) + values[index]);
		}
		
		return cache[key] = ret;
	}
};

// 解法2：二维数组dp
class Solution2
{
public:
	Solution2(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		vector<vector<int>> dp(weights.size(), vector<int>(space + 1, 0));

		for (int s = 0; s <= space; ++s)
		{
			if (s >= weights[0])
			{
				dp[0][s] = values[0];
			}
			else
			{
				dp[0][s] = 0;
			}
		}

		for (int i = 0; i < (int)weights.size(); ++i)
		{
			dp[i][0] = 0;
		}

		for (int i = 1; i < (int)weights.size(); ++i)
		{
			for (int s = 1; s <= space; ++s)
			{
				dp[i][s] = dp[i - 1][s];
				if (s >= weights[i])
				{
					dp[i][s] = max(dp[i][s], dp[i - 1][s - weights[i]] + values[i]);
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

// 解法3：一维数组dp
class Solution3
{
public:
	Solution3(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		vector<int> dp(space + 1, 0);

		for (int s = 0; s <= space; ++s)
		{
			if (s >= weights[0])
			{
				dp[s] = values[0];
			}
			else
			{
				dp[s] = 0;
			}
		}

		for (int i = 1; i < (int)weights.size(); ++i)
		{
			for (int s = space; s >= 0; --s)
			{
				if (s >= weights[i])
				{
					dp[s] = max(dp[s], dp[s - weights[i]] + values[i]);
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