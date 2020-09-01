// https://www.luogu.com.cn/problem/P2404

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(int n) : n(n) {}

	vector<vector<int>> solve()
	{
		result.clear();
		divide.clear();
		dfs(1, 0);
		return result;
	}

private:
	int n;
	vector<vector<int>> result;
	vector<int> divide;

	void dfs(int last, int sum)
	{
		if (sum == n)
		{
			result.push_back(divide);
			return;
		}

		for (int i = last; i + sum <= n; ++i)
		{
			divide.push_back(i);
			dfs(i, i + sum);
			divide.pop_back();
		}
	}
};

int main()
{
	int n;
	cin >> n;

	vector<vector<int>> result = Solution(n).solve();
	for (vector<int> divide : result)
	{
		if (divide.size() > 1)
		{
			cout << divide[0];
			for (int i = 1; i < (int)divide.size(); ++i)
			{
				cout << "+" << divide[i];
			}
			cout << endl;
		}
	}

	return 0;
}