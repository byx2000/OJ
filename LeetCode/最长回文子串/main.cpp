// https://leetcode-cn.com/problems/longest-palindromic-substring/

#include "../common/common.h"

class Solution 
{
public:
    string longestPalindrome(string s) 
    {
        this->s = s;
        cache = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));
        book = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));

        int l = 0, r = 0;
        int maxLen = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            for (int j = i; j < (int)s.size(); ++j)
            {
                if (dp(i, j) && j - i + 1 > maxLen)
                {
                    l = i;
                    r = j;
                    maxLen = j - i + 1;
                }
            }
        }

        return s.substr(l, maxLen);
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

int main()
{
    TEST(Assert::areEqual(Solution().longestPalindrome("babad"), "bab"));
    TEST(Assert::areEqual(Solution().longestPalindrome("cbbd"), "bb"));

	return 0;
}