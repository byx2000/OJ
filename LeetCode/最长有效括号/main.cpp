// https://leetcode-cn.com/problems/longest-valid-parentheses/

#include "../common/common.h"

// O(n) ��̬�滮
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

    // ��s[i]��β�����Ч�������г���
    int dp(int i)
    {
        if (i < 0) return 0;
        if (i == 0 || s[i] == '(') return 0;
        if (cache[i] != -1) return cache[i];

        // ִ�е����˵����s[i] >= 1 && s[i] == ')'

        if (s[i - 1] == '(') return cache[i] = dp(i - 2) + 2; // ����Ϊ��...()
        
        // ִ�е����˵������Ϊ��...))

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