// https://www.luogu.com.cn/problem/P2066

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<vector<int>>& value) : value(value) {}

	pair<long long, vector<pair<int, int>>> solve()
	{
		path = vector<vector<pair<int, int>>>(value.size(), vector<pair<int, int>>(value[0].size() + 1, make_pair(-1, -1)));
		long long res = dp(value.size() - 1, value[0].size());

		// 构造方案
		vector<pair<int, int>> output;
		int iCompany = value.size() - 1;
		int leftDevice = value[0].size();
		while (iCompany != -1 && leftDevice != -1)
		{
			pair<int, int> p = path[iCompany][leftDevice];
			if (p.first != -1 && p.second != -1)
			{
				output.push_back(make_pair(iCompany + 1, leftDevice - p.second));
			}
			else
			{
				if (leftDevice > 0)
				{
					output.push_back(make_pair(1, leftDevice));
				}
				else
				{
					output.push_back(make_pair(1, 0));
				}
			}
			iCompany = p.first;
			leftDevice = p.second;
		}

		return make_pair(res, output);
	}

private:
	vector<vector<int>> value;
	vector<vector<pair<int, int>>> path;

	// 将leftDevice台设备分配给公司0~公司iCompany获得的最大利润
	long long dp(int iCompany, int leftDevice)
	{
		if (iCompany == 0)
		{
			if (leftDevice <= 0)
			{
				return 0;
			}
			else
			{
				return value[0][leftDevice - 1];
			}
		}

		long long ret = -1;
		for (int i = leftDevice; i >= 1; --i)
		{
			long long t = dp(iCompany - 1, leftDevice - i) + value[iCompany][i - 1];
			if (t > ret)
			{
				ret = t;
				path[iCompany][leftDevice] = make_pair(iCompany - 1, leftDevice - i);
			}
		}

		long long t = dp(iCompany - 1, leftDevice);
		if (t > ret)
		{
			ret = t;
			path[iCompany][leftDevice] = make_pair(iCompany - 1, leftDevice);
		}

		return ret;
	}
};

int main()
{
	int nCompany, nDevice;
	cin >> nCompany >> nDevice;

	vector<vector<int>> value(nCompany, vector<int>(nDevice));
	for (int i = 0; i < nCompany; ++i)
	{
		for (int j = 0; j < nDevice; ++j)
		{
			cin >> value[i][j];
		}
	}

	pair<long long, vector<pair<int, int>>> res = Solution(value).solve();

	cout << res.first << endl;
	vector<pair<int, int>> output = res.second;
	for (int i = (int)output.size() - 1; i >= 0; --i)
	{
		cout << output[i].first << " " << output[i].second << endl;
	}

	return 0;
}