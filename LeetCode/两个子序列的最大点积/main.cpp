// https://leetcode-cn.com/problems/max-dot-product-of-two-subsequences/

#include "../common/common.h"

// O(m^2*n^2) 动态规划
class Solution1
{
public:
    Solution1(const vector<int>& a, const vector<int>& b)
        : a(a), b(b) {}

    int solve()
    {
        cache = vector<vector<int>>(a.size(), vector<int>(b.size()));
        book = vector<vector<bool>>(a.size(), vector<bool>(b.size(), false));

        int result = numeric_limits<int>::min();
        for (int i = 0; i < (int)a.size(); ++i)
        {
            for (int j = 0; j < (int)b.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> a, b;
    vector<vector<int>> cache;
    vector<vector<bool>> book;

    // 以a[i]结尾和b[j]结尾的子序列的最大点积
    int dp(int i, int j)
    {
        if (book[i][j]) return cache[i][j];
        book[i][j] = true;

        if (i == 0 || j == 0) return cache[i][j] = a[i] * b[j];

        int ret = a[i] * b[j];
        for (int m = 0; m < i; ++m)
        {
            for (int n = 0; n < j; ++n)
            {
                ret = max(ret, dp(m, n) + a[i] * b[j]);
            }
        }

        return cache[i][j] = ret;
    }
};

// O(mn) 动态规划
class Solution2
{
public:
    Solution2(const vector<int>& a, const vector<int>& b)
        : a(a), b(b) {}

    int solve()
    {
        cache = vector<vector<int>>(a.size(), vector<int>(b.size()));
        book = vector<vector<bool>>(a.size(), vector<bool>(b.size(), false));
        return dp(a.size() - 1, b.size() - 1);
    }

private:
    vector<int> a, b;
    vector<vector<int>> cache;
    vector<vector<bool>> book;

    // a[0]~a[i]和b[0]~b[j]子序列的最大点积
    int dp(int i, int j)
    {
        if (book[i][j]) return cache[i][j];
        book[i][j] = true;

        if (i == 0)
        {
            // 求max(a[0]*b[0], a[0]*b[1], ..., a[0]*b[j])
            int ret = a[0] * b[0];
            for (int k = 1; k <= j; ++k)
            {
                ret = max(ret, a[0] * b[k]);
            }
            return cache[i][j] = ret;
        }

        if (j == 0)
        {
            // 求max(a[0]*b[0], a[1]*b[0], ..., a[i]*b[0])
            int ret = a[0] * b[0];
            for (int k = 1; k <= i; ++k)
            {
                ret = max(ret, a[k] * b[0]);
            }
            return cache[i][j] = ret;
        }

        int r1 = dp(i, j - 1);
        int r2 = dp(i - 1, j);
        int r3 = dp(i - 1, j - 1);

        return cache[i][j] = max({ r1, r2, r3, r3 + a[i] * b[j], a[i] * b[j] });
    }
};

class Solution 
{
public:
    int maxDotProduct(vector<int>& a, vector<int>& b) 
    {
        //return Solution1(a, b).solve();
        return Solution2(a, b).solve();
    }
};

int main()
{
    Cases<vector<int>, vector<int>, int> cases
    {
        {{1}, {2}, 2},
        {{2}, {1, 2}, 4},
        {{2}, {1, -2}, 2},
        {{2, 1}, {2}, 4},
        {{-2, 1}, {2}, 2},
        {{2,1,-2,5}, {3,0,-6}, 18},
        {{3,-2}, {2,-6,7}, 21},
        {{-1,-1}, {1,1}, -1},
        {{-3,-8,3,-10,1,3,9}, {9,2,3,7,-9,1,-8,5,-1,-1}, 200},
    };

    test(&Solution::maxDotProduct, cases);

	return 0;
}