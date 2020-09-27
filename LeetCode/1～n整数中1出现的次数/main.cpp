// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/

#include "../common/common.h"

// 数位dp
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
            cnt += dp(0, i, i == digits[0]);
        }

        return cnt;
    }

private:
    int n;
    vector<int> digits;
    vector<int> pow10;
    vector<vector<vector<int>>> cache;

    // 分离出整数n的各位数字
    // 例如：n = 123 -> return [1, 2, 3]
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

    // 计算10^0~10^n的值
    // 例如：n = 5 -> return [1, 10, 100, 1000, 10000, 100000]
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

    // 第cur位为d
    // 若top = true, 则前cur位都已经取到最大值
    int dp(int cur, int d, bool top)
    {
        if (cache[cur][d][top] != -1) return cache[cur][d][top];

        if (cur == (int)digits.size() - 1) return cache[cur][d][top] = (d == 1) ? 1 : 0;

        int ret = 0;

        if (d == 1 && !top) ret += pow10[digits.size() - cur - 1];
        if (d == 1 && top) ret += n % pow10[digits.size() - cur - 1] + 1;

        int upper = top ? digits[cur + 1] : 9;
        for (int i = 0; i <= upper; ++i)
        {
            ret += dp(cur + 1, i, top && i == digits[cur + 1]);
        }

        return cache[cur][d][top] = ret;
    }
};

class Solution
{
public:
    int countDigitOne(int n)
    {
        return Solution1(n).solve();
    }
};

int main()
{
    Cases<int, int> cases
    {
        {0, 0},
        {12, 5},
        {13, 6},
        {100, 21},
    };

    test(&Solution::countDigitOne, cases);

	return 0;
}