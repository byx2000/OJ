// https://www.luogu.com.cn/problem/P1063

#include <iostream>
#include <vector>

using namespace std;

// 解法1：记忆化搜索
class Solution1
{
public:
	Solution1(const vector<int>& nums) : head(nums)
	{
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            head.push_back(nums[i]);
        }

        for (int i = 0; i < (int)head.size() - 1; ++i)
        {
            tail.push_back(head[i + 1]);
        }
        tail.push_back(head[0]);
	}

	int solve()
	{
        cache = vector<vector<int>>(head.size(), vector<int>(head.size(), -1));

        int n = (int)head.size() / 2;
        int res = -1;
        for (int i = 0; i < n; ++i)
        {
            res = max(res, dp(i, i + n - 1));
        }

        return res;
	}

private:
	vector<int> head, tail;
    vector<vector<int>> cache;

    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (i == j)
        {
            return cache[i][j] = 0;
        }

        int ret = -1;
        for (int k = i; k < j; ++k)
        {
            ret = max(ret, dp(i, k) + dp(k + 1, j) + head[i] * tail[k] * tail[j]);
        }

        return cache[i][j] = ret;
    }
};

int main()
{
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}

	cout << Solution1(nums).solve();

	return 0;
}