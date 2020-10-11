// https://www.luogu.com.cn/problem/P1799

#include <iostream>
#include <vector>

using namespace std;

class Solution1
{
public:
	Solution1(const vector<int>& nums) : nums(nums) {}

	int solve()
	{
		cache = vector<vector<int>>(nums.size(), vector<int>(nums.size() + 1, -1));

		int result = 0;
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			for (int c = 0; c <= i + 1; ++c)
			{
				result = max(result, dp(i, c));
			}
		}

		return result;
	}

private:
	vector<int> nums;
	vector<vector<int>> cache;

	// 在nums[0]~nujms[index]中删除c个数后，剩下的满足nums[k] == k的数的个数的最大值
	// 保证index + 1 >= c
	int dp(int index, int c)
	{
		if (cache[index][c] != -1)
		{
			return cache[index][c];
		}

		if (index == 0)
		{
			if (c == 0) return cache[index][c] = nums[0] == 1;
			else return cache[index][c] = 0;
		}

		int ret = 0;
		if (c >= 1) ret = dp(index - 1, c - 1); // 删除nums[index]
		if (index + 1 > c) // 不删除nums[index]
		{
			ret = max(ret, dp(index - 1, c) + (nums[index] == index - c + 1));
		}

		return cache[index][c] = ret;
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