// https://loj.ac/problem/2044

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

long long cache[12][10][10][2][2][2][2][2];

class Solution1
{
public:
	Solution1(long long n) : n(n) {}

	long long solve()
	{
		if (n == 0) return 0;
		memset(cache, -1, sizeof(cache));
		digits = getDigits(n);
		return dp(0, 0, 0, false, false, false, true, true);
	}

private:
	long long n;
	vector<long long> digits;

	vector<long long> getDigits(long long n)
	{
		vector<long long> v;
		while (n)
		{
			v.push_back(n % 10);
			n /= 10;
		}
		reverse(v.begin(), v.end());
		return v;
	}

	long long dp(int index,
		int last2, int last1, bool same,
		bool has4, bool has8,
		bool leading, bool top)
	{
		if (cache[index][last2][last1][same][has4][has8][leading][top] != -1)
			return cache[index][last2][last1][same][has4][has8][leading][top];

		if (index == digits.size())
			return cache[index][last2][last1][same][has4][has8][leading][top] = same ? 1 : 0;

		int upper = top ? digits[index] : 9;
		long long cnt = 0;
		for (int i = 0; i <= upper; ++i)
		{
			if (!((has4 && i == 8) || (has8 && i == 4)))
			{
				cnt += dp(index + 1,
					last1, i, !leading && (same || (last2 == last1 && last1 == i)),
					has4 || i == 4, has8 || i == 8,
					leading && i == 0, top && i == digits[index]);
			}
		}

		return cache[index][last2][last1][same][has4][has8][leading][top] = cnt;
	}
};

int main()
{
	long long a, b;
	cin >> a >> b;
	cout << Solution1(b).solve() - Solution1(a - 1).solve() << endl;
	return 0;
}
