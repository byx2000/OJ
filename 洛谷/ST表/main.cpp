// https://www.luogu.com.cn/problem/P3865

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <map>
#include <unordered_map>
#include <cmath>

using namespace std;

// 预处理O(n^2) 查询O(1)
class Solution1
{
public:
    Solution1(const vector<int>& nums)
        : nums(nums), max(vector<vector<int>>(nums.size(), vector<int>(nums.size())))
    {
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            max[i][i] = nums[i];
            for (int j = i + 1; j < (int)nums.size(); ++j)
            {
                max[i][j] = std::max(max[i][j - 1], nums[j]);
            }
        }
    }

    int queryMax(int i, int j)
    {
        return max[i][j];
    }

private:
    vector<int> nums;
    vector<vector<int>> max;
};

// 预处理O(nlogn) 查询O(1)
class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums)
    {
        log2 = vector<int>(nums.size() + 1);
        for (int i = 0; i < (int)log2.size(); ++i)
        {
            log2[i] = (int)(log(i) / log(2));
        }

        cache = vector<vector<int>>(nums.size(), vector<int>(log2[nums.size()] + 1, -1));
    }

    int queryMax(int i, int j)
    {
        int r = log2[j - i + 1];
        return max(dp(i, r), dp(j - (1 << r) + 1, r));
    }

private:
    vector<int> nums;
    vector<int> log2;
    vector<vector<int>> cache;

    // max(nums[i], nums[i+1], ..., nums[i+2^j-1])
    int dp(int i, int j)
    {
        if (cache[i][j] != -1) return cache[i][j];
        if (j == 0) return cache[i][j] = nums[i];
        return cache[i][j] = max(dp(i, j - 1), dp(i + (1 << (j - 1)), j - 1));
    }
};

int main()
{
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    //Solution1 solution(nums);
    Solution2 solution(nums);

    while (m--)
    {
        int i, j;
        cin >> i >> j;
        cout << solution.queryMax(i - 1, j - 1) << endl;
    }

    return 0;
}