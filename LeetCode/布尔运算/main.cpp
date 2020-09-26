// https://leetcode-cn.com/problems/boolean-evaluation-lcci/

#include "../common/common.h"

// O(n^3) 区间dp
class Solution1
{
public:
    Solution1(const string& expr, int result)
        : expr(expr), result(result) {}

    int solve()
    {
        for (char c : expr)
        {
            if (c == '0' || c == '1') operands.push_back(c - '0');
            else operators.push_back(c);
        }

        cache0 = vector<vector<int>>(operands.size(), vector<int>(operands.size(), -1));
        cache1 = vector<vector<int>>(operands.size(), vector<int>(operands.size(), -1));

        return (result == 0) ? dp0(0, operands.size() - 1) : dp1(0, operands.size() - 1);
    }

private:
    string expr;
    int result;
    vector<int> operands;
    string operators;
    vector<vector<int>> cache0, cache1;

    // 对operands[i]~operands[j]进行运算，得到0的方法数
    int dp0(int i, int j)
    {
        if (cache0[i][j] != -1) return cache0[i][j];
        if (i == j) return cache0[i][j] = (operands[i] == 0) ? 1 : 0;

        int count = 0;
        for (int k = i; k < j; ++k)
        {
            switch (operators[k])
            {
            case '&':
                count += dp0(i, k) * dp1(k + 1, j) + dp1(i, k) * dp0(k + 1, j) + dp0(i, k) * dp0(k + 1, j);
                break;
            case '|':
                count += dp0(i, k) * dp0(k + 1, j);
                break;
            case '^':
                count += dp0(i, k) * dp0(k + 1, j) + dp1(i, k) * dp1(k + 1, j);
                break;
            }
        }

        return cache0[i][j] = count;
    }

    // 对operands[i]~operands[j]进行运算，得到1的方法数
    int dp1(int i, int j)
    {
        if (cache1[i][j] != -1) return cache1[i][j];
        if (i == j) return cache1[i][j] = (operands[i] == 1) ? 1 : 0;

        int count = 0;
        for (int k = i; k < j; ++k)
        {
            switch (operators[k])
            {
            case '&':
                count += dp1(i, k) * dp1(k + 1, j);
                break;
            case '|':
                count += dp0(i, k) * dp1(k + 1, j) + dp1(i, k) * dp0(k + 1, j) + dp1(i, k) * dp1(k + 1, j);
                break;
            case '^':
                count += dp0(i, k) * dp1(k + 1, j) + dp1(i, k) * dp0(k + 1, j);
                break;
            }
        }

        return cache1[i][j] = count;
    }
};

class Solution
{
public:
    int countEval(string expr, int result)
    {
        return Solution1(expr, result).solve();
    }
};

int main()
{
    Cases<string, int, int> cases
    {
        {"1^0|0|1", 0, 2},
        {"0&0&0&1^1|0", 1, 10},
        {"0^1|0|1|1|0|0|0&0^0&0|0&0", 0, 109418},
    };

    test(&Solution::countEval, cases);

	return 0;
}