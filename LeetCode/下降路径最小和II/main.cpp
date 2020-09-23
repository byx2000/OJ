// https://leetcode-cn.com/problems/minimum-falling-path-sum-ii/

#include "../common/common.h"

// O(n^3) 动态规划
class Solution1
{
public:
    Solution1(const vector<vector<int>>& nums)
        : nums(nums), n(nums.size()) {}

    int solve()
    {
        cache = vector<vector<int>>(n, vector<int>(n));
        book = vector<vector<bool>>(n, vector<bool>(n, false));

        int result = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
        {
            result = min(result, dp(n - 1, i));
        }

        return result;
    }

private:
    vector<vector<int>> nums;
    int n;
    vector<vector<int>> cache;
    vector<vector<bool>> book;

    // 以(r, c)结尾的非零偏移下降路径最小和
    int dp(int r, int c)
    {
        if (book[r][c])
        {
            return cache[r][c];
        }
        book[r][c] = true;

        if (r == 0)
        {
            return cache[r][c] = nums[0][c];
        }

        int ret = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
        {
            if (i != c)
            {
                ret = min(ret, dp(r - 1, i) + nums[r][c]);
            }
        }

        return cache[r][c] = ret;
    }
};

// O(n^2) 动态规划
class Solution2
{
public:
    Solution2(const vector<vector<int>>& nums)
        : nums(nums), n(nums.size()) {}

    // 寻找数组的最小元素和第二小元素
    // 假设数组长度 >= 2
    void findMin(const vector<int>& v, int& min1, int& index1, int& min2, int& index2)
    {
        if (v[0] > v[1])
        {
            min1 = v[1];
            index1 = 1;
            min2 = v[0];
            index2 = 0;
        }
        else // v[0] <= v[1]
        {
            min1 = v[0];
            index1 = 0;
            min2 = v[1];
            index2 = 1;
        }

        for (int i = 2; i < (int)v.size(); ++i)
        {
            if (v[i] < min1) // v[i] < min1 <= min2
            {
                min2 = min1;
                index2 = index1;
                min1 = v[i];
                index1 = i;
            }
            else if (v[i] < min2) // min1 <= v[i] < min2
            {
                min2 = v[i];
                index2 = i;
            }
        }
    }

    int solve()
    {
        vector<int> dp(nums[0].begin(), nums[0].end());
        int min1, min2;
        int index1, index2;

        for (int i = 1; i < n; ++i)
        {
            findMin(dp, min1, index1, min2, index2);
            for (int j = 0; j < n; ++j)
            {
                if (j == index1)
                {
                    dp[j] = min2 + nums[i][j];
                }
                else
                {
                    dp[j] = min1 + nums[i][j];
                }
            }
        }
        
        return *min_element(dp.begin(), dp.end());
    }

private:
    vector<vector<int>> nums;
    int n;
};

class Solution 
{
public:
    int minFallingPathSum(vector<vector<int>>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    Cases<vector<vector<int>>, int> cases
    {
        {{{1,2,3},{4,5,6},{7,8,9}}, 13},
        {{{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2}}, 7},
    };

    test(&Solution::minFallingPathSum, cases);

	return 0;
}