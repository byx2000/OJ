// https://loj.ac/problem/10167

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// ÊýÎ»dp
class Solution1
{
public:
	Solution1(int n) : n(n) {}

	int solve()
	{
		digits = getDigits(n);
		cache = vector<vector<vector<int>>>(digits.size() + 1, vector<vector<int>>(10, vector<int>(2, -1)));
		return dp(0, 0, true);
	}

private:
	int n;
	vector<int> digits;
	vector<vector<vector<int>>> cache;

	vector<int> getDigits(int n)
	{
		vector<int> v;
		while (n)
		{
			v.push_back(n % 10);
			n /= 10;
		}
		reverse(v.begin(), v.end());
		return v;
	}

	int dp(int index, int last, bool top)
	{
		if (cache[index][last][top] != -1) return cache[index][last][top];
		if (index == digits.size()) return cache[index][last][top] = 1;
		int upper = top ? digits[index] : 9;
		int cnt = 0;
		for (int i = 0; i <= upper; ++i)
		{
			if (!(i == 4 || (last == 6 && i == 2)))
			{
				cnt += dp(index + 1, i, top && i == digits[index]);
			}
		}
		return cache[index][last][top] = cnt;
	}
};

int main()
{
	int a, b;
	cin >> a >> b;
	while (a != 0 && b != 0)
	{
		cout << Solution1(b).solve() - Solution1(a - 1).solve() << endl;
		cin >> a >> b;
	}

	return 0;
}
