// https://www.luogu.com.cn/problem/P1012

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Ì°ÐÄ
class Solution1
{
public:
	Solution1(const vector<string>& nums) : nums(nums) {}

	string solve()
	{
		sort(nums.begin(), nums.end(), 
			[](const string& a, const string& b) 
			{
				return a + b > b + a;
			});

		string res = "";
		for (string n : nums)
		{
			res += n;
		}

		return res;
	}

private:
	vector<string> nums;
};

int main()
{
	int n;
	cin >> n;

	vector<string> nums(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}

	cout << Solution1(nums).solve();

	return 0;
}