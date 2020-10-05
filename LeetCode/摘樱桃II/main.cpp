// https://leetcode-cn.com/problems/cherry-pickup-ii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<vector<int>>& nums)
        : nums(nums), row(nums.size()), col(nums[0].size()) {}

    int solve()
    {
        cache = vector<vector<vector<int>>>(row, vector<vector<int>>(col, vector<int>(col, -1)));
        return dp(0, 0, col - 1);
    }

private:
    vector<vector<int>> nums;
    int row, col;
    vector<vector<vector<int>>> cache; // 三维数组

    // 机器人1：(r, i) -> (r, x)
    // 机器人2：(r, j) -> (r, y)
    int dp(int r, int i, int j)
    {
        if (cache[r][i][j] != -1)
        {
            return cache[r][i][j];
        }

        // 起点
        if (r == row - 1)
        {
            return cache[r][i][j] = (i == j) ? nums[r][i] : nums[r][i] + nums[r][j];
        }

        int ret = 0;
        int d[3] = { -1, 0, 1 };
        for (int a = 0; a < 3; ++a)
        {
            for (int b = 0; b < 3; ++b)
            {
                int ni = i + d[a];
                int nj = j + d[b];
                if (ni >= 0 && ni < col && nj >= 0 && nj < col)
                {
                    ret = max(ret, dp(r + 1, ni, nj));
                }
            }
        }

        if (i == j)
        {
            ret += nums[r][i];
        }
        else
        {
            ret += (nums[r][i] + nums[r][j]);
        }

        return cache[r][i][j] = ret;
    }
};

class Solution 
{
public:
    int cherryPickup(vector<vector<int>>& nums) 
    {
        return Solution1(nums).solve();
    }
};

int main()
{
    Cases<vector<vector<int>>, int> cases
    {
        {{ {3,1,1},{2,5,1},{1,5,5},{2,1,1} }, 24},
        {{ {1,0,0,0,0,0,1},{2,0,0,0,0,3,0},{2,0,9,0,0,0,0},{0,3,0,5,4,0,0},{1,0,2,3,0,0,6} }, 28},
        {{ {1,0,0,3},{0,0,0,3},{0,0,3,3},{9,0,3,3} }, 22},
        {{ {1,1},{1,1} }, 4},
        {{ {4,1,5,7,1},{6,0,4,6,4},{0,9,6,3,5} }, 32},
    };

    test(&Solution::cherryPickup, cases);

	return 0;
}