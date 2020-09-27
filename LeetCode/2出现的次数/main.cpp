// https://leetcode-cn.com/problems/number-of-2s-in-range-lcci/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        if (n == 0) return 0;

        digits = getDigits(n);
        pow10 = getPowOf10(digits.size() - 1);
        cache = vector<vector<vector<int>>>(digits.size(), vector<vector<int>>(10, vector<int>(2, -1)));

        int cnt = 0;
        for (int i = 0; i <= digits[0]; ++i)
        {
            cnt += dp(digits.size() - 1, i, i == digits[0]);
        }

        return cnt;
    }

private:
    int n;
    vector<int> digits;
    vector<int> pow10;
    vector<vector<vector<int>>> cache;

    vector<int> getDigits(int n)
    {
        vector<int> digits;
        while (n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }

    vector<int> getPowOf10(int n)
    {
        vector<int> pow10(n + 1);
        pow10[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            pow10[i] = pow10[i - 1] * 10;
        }
        return pow10;
    }

    int dp(int layer, int d, bool top)
    {
        if (cache[layer][d][top] != -1) return cache[layer][d][top];

        if (layer == 0) return cache[layer][d][top] = (d == 2) ? 1 : 0;

        int cnt = 0;
        if (d == 2 && !top) cnt += pow10[layer];
        if (d == 2 && top) cnt += n % pow10[layer] + 1;

        int upper = top ? digits[digits.size() - layer] : 9;
        for (int i = 0; i <= upper; ++i)
        {
            cnt += dp(layer - 1, i, top && i == digits[digits.size() - layer]);
        }

        return cache[layer][d][top] = cnt;
    }
};

class Solution 
{
public:
    int numberOf2sInRange(int n) 
    {
        return Solution1(n).solve();
    }
};

int main()
{
    Cases<int, int> cases
    {
        {0, 0},
        {1, 0},
        {2, 1},
        {10, 1},
        {12, 2},
        {25, 9},
        {99, 20},
        {100, 20},
        {102, 21},
        {3628, 2132},
    };

    test(&Solution::numberOf2sInRange, cases);

	return 0;
}