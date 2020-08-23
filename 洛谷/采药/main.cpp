// https://www.luogu.com.cn/problem/P1048

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <set>

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

// 解法4：分支限界法（较差上界）
class Solution4
{
public:
	Solution4(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		int count = weights.size();

		// 计算最大单价
		vector<double> maxPrice(count);
		maxPrice[weights.size() - 1] = (double)values.back() / weights.back();
		for (int i = (int)weights.size() - 2; i >= 0; --i)
		{
			maxPrice[i] = max(maxPrice[i + 1], (double)values[i] / weights[i]);
		}

		priority_queue<State> pq;
		pq.push(State(0, 0, space, maxPrice));

		set<pair<int, int>> visited;

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			int currentIndex = state.index;
			int currentValue = state.value;
			int currentLeftSpace = state.leftSpace;

			// 禁止重复扩展节点
			pair<int, int> key(currentIndex, currentValue);
			if (visited.count(key) > 0)
			{
				continue;
			}
			visited.insert(key);

			if (currentIndex == weights.size())
			{
				return currentValue;
			}


			pq.push(State(currentIndex + 1, currentValue, currentLeftSpace, maxPrice));

			if (currentLeftSpace >= weights[currentIndex])
			{
				int newIndex = currentIndex + 1;
				int newLeftSpace = currentLeftSpace - weights[currentIndex];
				int newValue = currentValue + values[currentIndex];
				pq.push(State(newIndex, newValue, newLeftSpace, maxPrice));
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
		int value;
		int leftSpace;
		double upperBound;
		State(int index, int value, int leftSpace, const vector<double>& maxPrice)
			: index(index), value(value), leftSpace(leftSpace)
		{
			// 计算上界
			if (index >= (int)maxPrice.size())
			{
				upperBound = value;
			}
			else
			{
				upperBound = value + leftSpace * maxPrice[index];
			}
		}
		bool operator<(const State& s) const { return upperBound < s.upperBound; }
	};
};

// 解法5：分支限界法（较好上界）
class Solution5
{
public:
	Solution5(const vector<int>& weights, const vector<int>& values, int space)
		: weights(weights), values(values), space(space) {}

	int solve()
	{
		int count = weights.size();

		vector<Object> objects;
		for (int i = 0; i < count; ++i)
		{
			objects.push_back(Object(weights[i], values[i]));
		}

		// 排序
		sort(objects.begin(), objects.end());

		priority_queue<State> pq;
		pq.push(State(0, 0, space, objects));

		set<pair<int, int>> visited;

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			int currentIndex = state.index;
			int currentValue = state.value;
			int currentLeftSpace = state.leftSpace;

			// 禁止重复扩展节点
			pair<int, int> key(currentIndex, currentValue);
			if (visited.count(key) > 0)
			{
				continue;
			}
			visited.insert(key);

			if (currentIndex == weights.size())
			{
				return currentValue;
			}


			pq.push(State(currentIndex + 1, currentValue, currentLeftSpace, objects));

			if (currentLeftSpace >= objects[currentIndex].weight)
			{
				int newIndex = currentIndex + 1;
				int newLeftSpace = currentLeftSpace - objects[currentIndex].weight;
				int newValue = currentValue + objects[currentIndex].value;
				pq.push(State(newIndex, newValue, newLeftSpace, objects));
			}
		}

		return 0;
	}

private:
	vector<int> weights;
	vector<int> values;
	int space;

	struct Object
	{
		int weight;
		int value;
		double price;
		Object(int weight, int value) : weight(weight), value(value), price((double)value / weight) {}
		bool operator<(const Object& o) const { return price > o.price; }
	};

	struct State
	{
		int index;
		int value;
		int leftSpace;
		double upperBound;
		State(int index, int value, int leftSpace, const vector<Object>& objects)
			: index(index), value(value), leftSpace(leftSpace)
		{
			// 计算上界
			if (index >= (int)objects.size())
			{
				upperBound = value;
			}
			else
			{
				upperBound = value + leftSpace * objects[index].price;
			}
		}
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
	//cout << Solution4(weights, values, space).solve();
	cout << Solution5(weights, values, space).solve();

	return 0;
}