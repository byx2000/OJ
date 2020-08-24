// https://www.luogu.com.cn/problem/P1090

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 贪心算法
class Solution
{
public:
	Solution(const vector<int>& nums) : nums(nums) {}

	int solve()
	{
		// 小根堆
		priority_queue<int, vector<int>, greater<int>> pq;
		
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			pq.push(nums[i]);
		}

		int score = 0;
		while (pq.size() >= 2)
		{
			int a = pq.top();
			pq.pop();
			int b = pq.top();
			pq.pop();
			score += (a + b);
			pq.push(a + b);
		}

		return score;
	}

private:
	vector<int> nums;
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

	cout << Solution(nums).solve();

	return 0;
}