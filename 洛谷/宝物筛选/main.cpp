// https://www.luogu.com.cn/problem/P1776

#include <iostream>
#include <vector>

using namespace std;

// 解法1：转化为01背包问题（TLE）
class Solution1
{
public:
	Solution1(const vector<int>& weights, const vector<int>& values, const vector<int>& amounts,int space)
		: weights(weights), values(values), amounts(amounts), space(space) {}

	int solve()
	{
		vector<int> newWeights, newValues;
		for (int i = 0; i < (int)weights.size(); ++i)
		{
			for (int j = 0; j < amounts[i]; ++j)
			{
				newWeights.push_back(weights[i]);
				newValues.push_back(values[i]);
			}
		}

		vector<int> dp(space + 1);

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			if (leftSpace >= newWeights[0])
			{
				dp[leftSpace] = newValues[0];
			}
			else
			{
				dp[leftSpace] = 0;
			}
		}

		for (int index = 1; index < (int)newWeights.size(); ++index)
		{
			for (int leftSpace = space; leftSpace >= 0; --leftSpace)
			{
				if (leftSpace >= newWeights[index])
				{
					dp[leftSpace] = max(dp[leftSpace], dp[leftSpace - newWeights[index]] + newValues[index]);
				}
			}
		}

		return dp[space];
	}

private:
	vector<int> weights, values, amounts;
	int space;
};

// 解法2：转化为01背包问题 + 二进制分组优化
class Solution2
{
public:
	Solution2(const vector<int>& weights, const vector<int>& values, const vector<int>& amounts, int space)
		: weights(weights), values(values), amounts(amounts), space(space) {}

	int solve()
	{
		vector<int> newWeights, newValues;
		for (int i = 0; i < (int)weights.size(); ++i)
		{
			// 二进制分组
			int p = 1;
			int s = 0;
			
			while (p <= amounts[i])
			{
				newWeights.push_back(weights[i] * p);
				newValues.push_back(values[i] * p);
				amounts[i] -= p;
				p *= 2;
			}

			if (amounts[i] > 0)
			{
				newWeights.push_back(weights[i] * amounts[i]);
				newValues.push_back(values[i] * amounts[i]);
			}
		}

		vector<int> dp(space + 1);

		for (int leftSpace = 0; leftSpace <= space; ++leftSpace)
		{
			if (leftSpace >= newWeights[0])
			{
				dp[leftSpace] = newValues[0];
			}
			else
			{
				dp[leftSpace] = 0;
			}
		}

		for (int index = 1; index < (int)newWeights.size(); ++index)
		{
			for (int leftSpace = space; leftSpace >= 0; --leftSpace)
			{
				if (leftSpace >= newWeights[index])
				{
					dp[leftSpace] = max(dp[leftSpace], dp[leftSpace - newWeights[index]] + newValues[index]);
				}
			}
		}

		return dp[space];
	}

private:
	vector<int> weights, values, amounts;
	int space;
};

int main()
{
	int count, space;
	cin >> count >> space;

	vector<int> weights(count);
	vector<int> values(count);
	vector<int> amounts(count);
	for (int i = 0; i < count; ++i)
	{
		cin >> values[i] >> weights[i] >> amounts[i];
	}

	//cout << Solution1(weights, values, amounts, space).solve();
	cout << Solution2(weights, values, amounts, space).solve();

	return 0;
}