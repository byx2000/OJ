// https://www.luogu.com.cn/problem/P1049

#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(int capacity, const vector<int>& volumes)
		: capacity(capacity), volumes(volumes) {}

	int solve()
	{
		cache.clear();
		return dp(volumes.size() - 1, capacity);
	}

private:
	int capacity;
	vector<int> volumes;
	map<pair<int, int>, int> cache;

	int dp(int index, int leftSpace)
	{
		pair<int, int> key(index, leftSpace);

		if (cache.count(key) > 0)
		{
			return cache[key];
		}

		if (index == 0)
		{
			if (leftSpace >= volumes[0])
			{
				return cache[key] = leftSpace - volumes[0];
			}
			else
			{
				return cache[key] = leftSpace;
			}
		}

		int ret = dp(index - 1, leftSpace);
		if (leftSpace >= volumes[index])
		{
			ret = min(ret, dp(index - 1, leftSpace - volumes[index]));
		}

		return cache[key] = ret;
	}
};

// 解法2：二维数组dp
class Solution2
{
public:
	Solution2(int capacity, const vector<int>& volumes)
		: capacity(capacity), volumes(volumes) {}

	int solve()
	{
		vector<vector<int>> dp(volumes.size(), vector<int>(capacity + 1, 0));

		for (int leftSpace = 0; leftSpace <= capacity; ++leftSpace)
		{
			if (leftSpace >= volumes[0])
			{
				dp[0][leftSpace] = leftSpace - volumes[0];
			}
			else
			{
				dp[0][leftSpace] = leftSpace;
			}
		}

		for (int index = 1; index < (int)volumes.size(); ++index)
		{
			for (int leftSpace = 0; leftSpace <= capacity; ++leftSpace)
			{
				dp[index][leftSpace] = dp[index - 1][leftSpace];
				if (leftSpace >= volumes[index])
				{
					dp[index][leftSpace] = min(dp[index][leftSpace], dp[index - 1][leftSpace - volumes[index]]);
				}
			}
		}

		return dp[volumes.size() - 1][capacity];
	}

private:
	int capacity;
	vector<int> volumes;
};

// 解法3：一维数组dp
class Solution3
{
public:
	Solution3(int capacity, const vector<int>& volumes)
		: capacity(capacity), volumes(volumes) {}

	int solve()
	{
		vector<int> dp(capacity + 1, 0);

		for (int leftSpace = 0; leftSpace <= capacity; ++leftSpace)
		{
			if (leftSpace >= volumes[0])
			{
				dp[leftSpace] = leftSpace - volumes[0];
			}
			else
			{
				dp[leftSpace] = leftSpace;
			}
		}

		for (int index = 1; index < (int)volumes.size(); ++index)
		{
			for (int leftSpace = capacity; leftSpace >= 0; --leftSpace)
			{
				if (leftSpace >= volumes[index])
				{
					dp[leftSpace] = min(dp[leftSpace], dp[leftSpace - volumes[index]]);
				}
			}
		}

		return dp[capacity];
	}

private:
	int capacity;
	vector<int> volumes;
};

int main()
{
	int capacity, count;
	cin >> capacity >> count;

	vector<int> volumes;
	for (int i = 0; i < count; ++i)
	{
		int volume;
		cin >> volume;
		volumes.push_back(volume);
	}

	//cout << Solution1(capacity, volumes).solve();
	//cout << Solution2(capacity, volumes).solve();
	cout << Solution3(capacity, volumes).solve();

	return 0;
}