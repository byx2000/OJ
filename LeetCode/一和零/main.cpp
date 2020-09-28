// https://leetcode-cn.com/problems/ones-and-zeroes/

#include "../common/common.h"

class Solution1
{
public:
	Solution1(const vector<string>& strs, int m, int n)
		: strs(strs), m(m), n(n) {}

	int solve()
	{
		// 计算每个字符串包含0和1的数量
		for (string s : strs)
		{
			vector<int> c(2, 0);
			for (char ch : s)
			{
				c[ch - '0']++;
			}
			nums.push_back(c);
		}

		cache = vector<vector<vector<int>>>(strs.size(), vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

		return dp(strs.size() - 1, m, n);
	}

private:
	vector<string> strs;
	int m, n;
	vector<vector<int> > nums;
	vector<vector<vector<int>>> cache;

	int dp(int index, int c0, int c1)
	{
		if (cache[index][c0][c1] != -1) return cache[index][c0][c1];

		if (index == 0)
		{
			if (c0 >= nums[0][0] && c1 >= nums[0][1])
				return cache[index][c0][c1] = 1;
			else return cache[index][c0][c1] = 0;
		}

		int ret = dp(index - 1, c0, c1);
		if (c0 >= nums[index][0] && c1 >= nums[index][1])
			ret = max(ret, dp(index - 1, c0 - nums[index][0], c1 - nums[index][1]) + 1);

		return cache[index][c0][c1] = ret;
	}
};

class Solution 
{
public:
	int findMaxForm(vector<string>& strs, int m, int n) 
	{
		return Solution1(strs, m, n).solve();
	}
};

int main()
{
	Cases<vector<string>, int, int, int> cases
	{
		{{"10", "0001", "111001", "1", "0"}, 5, 3, 4},
		{{"10", "0", "1"}, 1, 1, 2},
	};

	test(&Solution::findMaxForm, cases);

	return 0;
}