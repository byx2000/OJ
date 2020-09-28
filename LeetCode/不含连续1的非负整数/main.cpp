// https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/

#include "../common/common.h"

// ÊýÎ»dp
class Solution1
{
public:
	Solution1(int n) : n(n) {}

	int solve()
	{
		bin = toBin(n);
		cache = vector<vector<vector<int>>>(bin.size() + 1, vector<vector<int>>(2, vector<int>(2, -1)));
		return dfs(0, 0, true);
	}

private:
	int n;
	vector<int> bin;
	vector<vector<vector<int>>> cache;

	vector<int> toBin(int n)
	{
		vector<int> bin;
		while (n)
		{
			bin.push_back(n % 2);
			n /= 2;
		}
		reverse(bin.begin(), bin.end());
		return bin;
	}

	int dfs(int index, int last, int top)
	{
		if (cache[index][last][top] != -1) return cache[index][last][top];

		if (index == bin.size()) return cache[index][last][top] = 1;
		int upper = top ? bin[index] : 1;

		int cnt = dfs(index + 1, 0, top && bin[index] == 0);
		if (last == 0 && upper == 1)
			cnt += dfs(index + 1, 1, top && bin[index] == 1);

		return cache[index][last][top] = cnt;
	}
};

class Solution 
{
public:
	int findIntegers(int num) 
	{
		return Solution1(num).solve();
	}
};

int main()
{
	Cases<int, int> cases
	{
		{5, 5},
		{25, 13},
		{100, 34},
		{2375, 314},
	};

	test(&Solution::findIntegers, cases);

	return 0;
}