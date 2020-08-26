// https://www.luogu.com.cn/problem/P1140

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <vector>

using namespace std;

// 计算基因相似度
int similarity(char a, char b)
{
	map<char, int> m;
	m['A'] = 0;
	m['C'] = 1;
	m['G'] = 2;
	m['T'] = 3;
	m[' '] = 4;

	static int table[5][5] =
	{
		5, -1, -2, -1, -3,
		-1, 5, -3, -2, -4,
		-2, -3, 5, -2, -2,
		-1, -2, -2, 5, -1,
		-3, -4, -2, -1, numeric_limits<int>::min(),
	};

	return table[m[a]][m[b]];
}

class Solution
{
public:
	Solution(const string& s1, const string& s2)
		: s1(s1), s2(s2) {}

	int solve()
	{
		cache = vector<vector<int>>(s1.size() + 1, vector<int>(s2.size() + 1, -1));
		return dp(s1.size(), s2.size());
	}

private:
	string s1, s2;
	vector<vector<int>> cache;

	// s1的前i个字符和s2的前j个字符的最大相似度
	int dp(int i, int j)
	{
		if (i == 0 && j == 0)
		{
			return 0;
		}
		
		if (cache[i][j] != -1)
		{
			return cache[i][j];
		}

		if (i == 0)
		{
			return cache[i][j] = dp(0, j - 1) + similarity(s2[j - 1], ' ');
		}

		if (j == 0)
		{
			return cache[i][j] = dp(i - 1, 0) + similarity(s1[i - 1], ' ');
		}

		int ret = dp(i - 1, j - 1) + similarity(s1[i - 1], s2[j - 1]);
		ret = max(ret, dp(i - 1, j) + similarity(s1[i - 1], ' '));
		ret = max(ret, dp(i, j - 1) + similarity(s2[j - 1], ' '));

		return cache[i][j] = ret;
	}
};

int main()
{
	int n, m;
	string s1, s2;
	cin >> n >> s1 >> m >> s2;

	cout << Solution(s1, s2).solve();

	return 0;
}