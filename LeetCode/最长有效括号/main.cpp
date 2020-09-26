// https://leetcode-cn.com/problems/longest-valid-parentheses/

#include "../common/common.h"

// O(n) 动态规划
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<int>(s.size(), -1);

        int result = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            result = max(result, dp(i));
        }

        return result;
    }

private:
    string s;
    vector<int> cache;

    // 以s[i]结尾的最长有效括号序列长度
    int dp(int i)
    {
        if (i < 0) return 0;
        if (i == 0 || s[i] == '(') return 0;
        if (cache[i] != -1) return cache[i];

        // 执行到这里，说明：s[i] >= 1 && s[i] == ')'

        if (s[i - 1] == '(') return cache[i] = dp(i - 2) + 2; // 序列为：...()
        
        // 执行到这里，说明序列为：...))

        int r = dp(i - 1);
        if (r == 0) return cache[i] = 0;
        if (i - r - 1 < 0) return cache[i] = 0;
        if (s[i - r - 1] != '(') return cache[i] = 0;
        return cache[i] = r + 2 + dp(i - r - 2);
    }
};

class Solution 
{
public:
    int longestValidParentheses(string s) 
    {
        return Solution1(s).solve();
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"", 0},
        {"(()", 2},
        {")()())", 4},
        {"())((())", 4},
    };

    test(&Solution::longestValidParentheses, cases);

	return 0;
}