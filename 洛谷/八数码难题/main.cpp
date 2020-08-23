// https://www.luogu.com.cn/problem/P1379

#include <iostream>
#include <string>
#include <queue>
#include <set>

using namespace std;

// 左移
bool left(string& s)
{
	int i = s.find('0');
	if (i % 3 == 0)
	{
		return false;
	}
	swap(s[i], s[i - 1]);
	return true;
}

// 右移
bool right(string& s)
{
	int i = s.find('0');
	if (i % 3 == 2)
	{
		return false;
	}
	swap(s[i], s[i + 1]);
	return true;
}

// 下移
bool down(string& s)
{
	int i = s.find('0');
	if (i >= 6)
	{
		return false;
	}
	swap(s[i], s[i + 3]);
	return true;
}

// 上移
bool up(string& s)
{
	int i = s.find('0');
	if (i <= 2)
	{
		return false;
	}
	swap(s[i], s[i - 3]);
	return true;
}

// 解法1：BFS
class Solution1
{
public:
	Solution1(const string& initial, const string& target)
		: initial(initial), target(target) {}

	int solve()
	{
		vector<bool(*)(string&)> transform{ left, right, down, up };

		queue<pair<string, int>> q;
		q.push(pair<string, int>(initial, 0));
		set<string> visited;

		while (!q.empty())
		{
			pair<string, int> current = q.front();
			q.pop();
			string s = current.first;
			int step = current.second;

			if (s == target)
			{
				return step;
			}

			if (visited.count(s) > 0)
			{
				continue;
			}
			visited.insert(s);

			for (int i = 0; i < (int)transform.size(); ++i)
			{
				string next = s;
				if (transform[i](next))
				{
					q.push(pair<string, int>(next, step + 1));
				}
			}
		}

		return 0;
	}

private:
	string initial;
	string target;
};

// 解法2：分支限界法
class Solution2
{
public:
	Solution2(const string& initial, const string& target)
		: initial(initial), target(target) {}

	int solve()
	{
		vector<bool(*)(string&)> transform{ left, right, down, up };

		priority_queue<State, vector<State>, greater<State>> pq;
		pq.push(State(initial, 0, target));
		set<string> visited;

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			string s = state.s;
			int step = state.step;

			if (visited.count(s) > 0)
			{
				continue;
			}
			visited.insert(s);

			if (s == target)
			{
				return step;
			}

			for (int i = 0; i < (int)transform.size(); ++i)
			{
				string next = s;
				if (transform[i](next))
				{
					pq.push(State(next, step + 1, target));
				}
			}
		}

		return 0;
	}

private:
	string initial;
	string target;

	struct State
	{
		string s;
		int step;
		int lowerBound;
		State(const string& s, int step, const string& target)
			: s(s), step(step)
		{
			lowerBound = step;
			for (int i = 0; i < (int)target.size(); ++i)
			{
				if (s[i] != target[i])
				{
					lowerBound++;
				}
			}
		}
		bool operator>(const State& s) const { return lowerBound > s.lowerBound; }
	};
};

int main()
{
	string initial;
	cin >> initial;

	//cout << Solution1(initial, "123804765").solve();
	cout << Solution2(initial, "123804765").solve();

	return 0;
}