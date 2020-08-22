// https://www.luogu.com.cn/problem/P1048

#include <iostream>
#include <vector>
#include <map>
#include <queue>

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

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			if (leftSpace >= weights[0])
			{
				dp[0][leftSpace] = values[0];
			}
			else
			{
				dp[0][leftSpace] = 0;
			}
		}

		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
			{
				dp[index][leftSpace] = dp[index - 1][leftSpace];
				if (leftSpace >= weights[index])
				{
					dp[index][leftSpace] = max(dp[index][leftSpace], dp[index - 1][leftSpace - weights[index]] + values[index]);
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

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			if (leftSpace >= weights[0])
			{
				dp[leftSpace] = values[0];
			}
			else
			{
				dp[leftSpace] = 0;
			}
		}

		for (int index = 1; index < (int)weights.size(); ++index)
		{
			for (int leftSpace = space; leftSpace >= 0; --leftSpace)
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

// 解法4：分支限界法
class Solution4
{
public:
	Solution4(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		// 计算最大单价
		double maxPrice = -1;
		for (int i = 0; i < (int)weights.size(); ++i)
		{
			maxPrice = max(maxPrice, (double)values[i] / weights[i]);
		}

		priority_queue<State> pq;
		pq.push(State(0, space, 0, space * maxPrice));

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			int index = state.index;
			int leftSpace = state.leftSpace;
			int value = state.value;

			cout << index << " " << leftSpace << " " << value << " " << state.upperBound << endl;

			if (index == weights.size())
			{
				return value;
			}

			pq.push(State(index + 1, leftSpace, value, leftSpace * maxPrice));

			if (leftSpace >= weights[index])
			{
				pq.push(State(index + 1, leftSpace - weights[index], value + values[index], (leftSpace - weights[index]) * maxPrice));
			}
		}

		return 0;
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;

	struct State
	{
		int index;
		int leftSpace;
		int value;
		double upperBound;
		State(int index, int leftSpace, int value, double upperBound)
			: index(index), leftSpace(leftSpace), value(value), upperBound(upperBound) {}
		bool operator<(const State& s) const { return upperBound < s.upperBound; }
	};
};

int main()
{
	int count, space;
	cin >> space >> count;

	vector<int> weights(count);
	vector<int> values(count);

	for (int i = 0; i < count; ++i)
	{
		cin >> weights[i] >> values[i];
	}

	//cout << Solution1(weights, values, space).solve();
	//cout << Solution2(weights, values, space).solve();
	//cout << Solution3(weights, values, space).solve();
	cout << Solution4(weights, values, space).solve();

	return 0;
}