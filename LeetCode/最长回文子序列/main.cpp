// https://leetcode-cn.com/problems/longest-palindromic-subsequence/

#include "../common/common.h"

// O(n^4) 动态规划
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));

        int result = -1;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            for (int j = 0; j < (int)s.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    string s;
    vector<vector<int>> cache;

    // 以s[i]开头、s[j]结尾的最长回文子序列长度
    // 假设i <= j
    int dp(int i, int j)
    {
        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (i == j)
        {
            return cache[i][j] = 1;
        }
        
        if (i + 1 == j)
        {
            return cache[i][j] = (s[i] == s[j]) ? 2 : 0;
        }

        if (s[i] != s[j])
        {
            return cache[i][j] = 0;
        }

        int ret = (i == j) ? 1 : 2;
        for (int a = i + 1; a <= j - 1; ++a)
        {
            for (int b = a; b <= j - 1; ++b)
            {
                ret = max(ret, dp(a, b) + 2);
            }
        }

        return cache[i][j] = ret;
    }
};

// O(n^2) 动态规划
class Solution2
{
public:
    Solution2(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));

        int result = -1;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            for (int j = 0; j < (int)s.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    string s;
    vector<vector<int>> cache;

    // s[i]~s[j]的最长回文子序列长度
    int dp(int i, int j)
    {
        if (i > j)
        {
            return 0;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (i == j)
        {
            return cache[i][j] = 1;
        }

        if (s[i] == s[j])
        {
            return cache[i][j] = 2 + dp(i + 1, j - 1);
        }
        else
        {
            return cache[i][j] = max(dp(i + 1, j), dp(i, j - 1));
        }
    }
};

class Solution 
{
public:
    int longestPalindromeSubseq(string s) 
    {
        //return Solution1(s).solve();
        return Solution2(s).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("a"), 1));
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("aa"), 2));
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("ab"), 1));/**/
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("aaa"), 3));
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("bbbab"), 4));
    TEST(Assert::areEqual(Solution().longestPalindromeSubseq("cbbd"), 2));/**/

	return 0;
}