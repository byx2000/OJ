// http://poj.org/problem?id=1465

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

// 解法1
class Solution1
{
public:
	Solution1(int n, const vector<int>& digits)
		: n(n), digits(digits) {}

	string solve()
	{
		if (n == 0)
		{
			return "0";
		}

		sort(digits.begin(), digits.end());

		queue<string> q;
		for (int i = 0; i < (int)digits.size(); ++i)
		{
			if (digits[i] != 0)
			{
				q.push(string(1, digits[i] + '0'));
			}
		}

		vector<bool> book(n, false);

		while (!q.empty())
		{
			string current = q.front();
			q.pop();

			int r = remain(current, n);

			if (r == 0)
			{	
				return current;
			}

			if (book[r])
			{
				continue;
			}
			book[r] = true;

			for (int i = 0; i < (int)digits.size(); ++i)
			{
				string next = current + string(1, digits[i] + '0');
				q.push(next);
			}
		}

		return "0";
	}

private:
	int n;
	vector<int> digits;

	int remain(const string& n, int m)
	{
		int r = 0;
		for (int i = 0; i < (int)n.size(); ++i)
		{
			r = (r * 10 + (n[i] - '0')) % m;
		}
		return r;
	}
};

// 解法2
class Solution2
{
public:
	Solution2(int n, const vector<int>& digits)
		: n(n), digits(digits) {}

	string solve()
	{
		if (n == 0)
		{
			return "0";
		}

		sort(digits.begin(), digits.end());

		queue<State> q;
		vector<State> path;

		for (int i = 0; i < (int)digits.size(); ++i)
		{
			if (digits[i] != 0)
			{
				q.push(State(digits[i], digits[i] % n, -1));
			}
		}

		vector<bool> book(n, false);

		while (!q.empty())
		{
			State state = q.front();
			q.pop();
			path.push_back(state);
			int remain = state.remain;

			if (remain == 0)
			{
				string s = "";
				s.push_back(state.digit + '0');
				int lastIndex = state.lastIndex;
				while (lastIndex != -1)
				{
					s.push_back(path[lastIndex].digit + '0');
					lastIndex = path[lastIndex].lastIndex;
				}
				reverse(s.begin(), s.end());

				return s;
			}

			if (book[remain])
			{
				continue;
			}
			book[remain] = true;

			for (int i = 0; i < (int)digits.size(); ++i)
			{
				q.push(State(digits[i], (remain * 10 + digits[i]) % n, (int)path.size() - 1));
			}
		}

		return "0";
	}

private:
	int n;
	vector<int> digits;

	struct State
	{
		int digit;
		int remain;
		int lastIndex;
		State(int digit, int remain, int lastIndex)
			: digit(digit), remain(remain), lastIndex(lastIndex) {}
	};
};

int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		vector<int> digits(m);
		for (int i = 0; i < m; ++i)
		{
			cin >> digits[i];
		}

		//cout << Solution1(n, digits).solve() << endl;
		cout << Solution2(n, digits).solve() << endl;
	}

	return 0;
}