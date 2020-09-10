// https://leetcode-cn.com/problems/palindromic-substrings/

#include "../common/common.h"

// 记忆化搜索
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));
        book = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));

        int count = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            for (int j = i; j < (int)s.size(); ++j)
            {
                if (dp(i, j))
                {
                    count++;
                }
            }
        }

        return count;
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
    int countSubstrings(string s) 
    {
        return Solution1(s).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().countSubstrings("abc"), 3));
    TEST(Assert::areEqual(Solution().countSubstrings("aaa"), 6));

	return 0;
}