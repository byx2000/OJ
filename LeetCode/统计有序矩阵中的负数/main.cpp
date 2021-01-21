// https://leetcode-cn.com/problems/count-negative-numbers-in-a-sorted-matrix/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<vector<int>>& grid) : grid(grid) {}

    int solve()
    {
        int r = grid.size();
        int c = grid[0].size();
        int cnt = 0;
        for (int i = 0; i < r; ++i)
        {
            // 找到该行从左到右第一个负数
            int left = 0, right = c - 1;
            while (right - left > 3)
            {
                int mid = left + (right - left) / 2;
                if (grid[i][mid] >= 0) left = mid + 1;
                else if (grid[i][mid] < 0) right = mid;
            }

            while (left <= right)
            {
                if (grid[i][left] < 0)
                {
                    cnt += c - left;
                    break;
                }
                left++;
            }
        }
        return cnt;
    }

private:
    vector<vector<int>> grid;
};

class Solution2
{
public:
    Solution2(const vector<vector<int>>& grid) : grid(grid) {}

    int solve()
    {
        int r = grid.size();
        int c = grid[0].size();
        int cnt = 0;
        
        // 找到第一行第一个负数的位置
        int pos = c;
        for (int i = 0; i < c; ++i)
        {
            if (grid[0][i] < 0)
            {
                pos = i;
                cnt += c - i;
                break;
            }
        }

        // 计算余下的行
        for (int i = 1; i < r; ++i)
        {
            for (int j = pos - 1; j >= 0; --j)
            {
                if (grid[i][j] >= 0)
                {
                    pos = j + 1;
                    cnt += c - j - 1;
                    break;
                }

                if (j == 0) cnt += c;
            }
        }

        return cnt;
    }

private:
    vector<vector<int>> grid;
};


class Solution
{
public:
    int countNegatives(vector<vector<int>>& grid)
    {
        //return Solution1(grid).solve();
        return Solution2(grid).solve();
    }
};

int main()
{
    Cases<vector<vector<int>>, int> cases
    {
        {{{5,1,0},{-5,-5,-5}}, 3},
        {{{3,-1,-3,-3,-3},{2,-2,-3,-3,-3},{1,-2,-3,-3,-3},{0,-3,-3,-3,-3}}, 16},
        {{{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}}, 8},
        {{{3,2},{1,0}}, 0},
        {{{1,-1},{-1,-1}}, 3},
        {{{-1}}, 1},
    };

    test(&Solution::countNegatives, cases);

	return 0;
}