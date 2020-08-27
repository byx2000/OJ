// https://www.luogu.com.cn/problem/P1223

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 贪心算法：短任务优先
class Solution
{
public:
	Solution(const vector<int>& time) : time(time) {}

	pair<vector<int>, double> solve()
	{
		vector<pair<int, int>> v(time.size());
		for (int i = 0; i < (int)time.size(); ++i)
		{
			v[i] = make_pair(i + 1, time[i]);
		}

		sort(v.begin(), v.end(), 
			[](const pair<int, int>& p1, const pair<int, int>& p2)
			{
				return p1.second < p2.second;
			});

		vector<int> res(v.size());
		double waitTime = 0;
		double totalTime = 0;
		for (int i = 0; i < (int)v.size(); ++i)
		{
			res[i] = v[i].first;
			waitTime += totalTime;
			totalTime += v[i].second;
		}

		return make_pair(res, waitTime / v.size());
	}

private:
	vector<int> time;
};

int main()
{
	int n;
	cin >> n;

	vector<int> time(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> time[i];
	}

	pair<vector<int>, double> res = Solution(time).solve();

	for (int i = 0; i < (int)res.first.size(); ++i)
	{
		cout << res.first[i] << " ";
	}
	cout << endl;
	cout << fixed << setprecision(2) << res.second;

	return 0;
}