// https://leetcode-cn.com/problems/longest-palindromic-substring/

#include "../common/common.h"

// 记忆化搜索
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    string solve()
    {
        cache = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));
        book = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));

        for (int len = s.size(); len >= 1; --len)
        {
            for (int start = 0; start + len <= (int)s.size(); ++start)
            {
                if (dp(start, start + len - 1))
                {
                    return s.substr(start, len);
                }
            }
        }

        return "";
    }

private:
    string s;
    vector<vector<bool>> cache, book;

    // 子串s[i]~s[j]是否为回文串
    bool dp(int i, int j)
    {
        if (book[i][j])
        {
            return cache[i][j];
        }
        book[i][j] = true;

        if (i == j)
        {
            return cache[i][j] = true;
        }
        else if (i + 1 == j)
        {
            return cache[i][j] = s[i] == s[j];
        }

        if (s[i] != s[j])
        {
            return cache[i][j] = false;
        }
        else
        {
            return cache[i][j] = dp(i + 1, j - 1);
        }
    }
};

class Solution 
{
public:
    string longestPalindrome(string s) 
    {
        return Solution1(s).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().longestPalindrome("babad"), "bab"));
    TEST(Assert::areEqual(Solution().longestPalindrome("cbbd"), "bb"));

	return 0;
}