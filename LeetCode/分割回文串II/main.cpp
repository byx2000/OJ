// https://leetcode-cn.com/problems/palindrome-partitioning-ii/

#include "../common/common.h"

// O(n^3) 动态规划
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        // dp[i]表示将s[0]~s[i]切分成若干回文串所需的最少切分数
        vector<int> dp(s.size());

        dp[0] = 0;
        for (int i = 1; i < (int)s.size(); ++i)
        {
            dp[i] = dp[i - 1] + 1;
            for (int j = i - 1; j >= 0; --j)
            {
                if (isPalindrome(j, i))
                {
                    if (j > 0)
                    {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                    else
                    {
                        dp[i] = 0;
                    }
                }
            }
        }

        return dp.back();
    }

private:
    string s;

    // 判断s[i]~s[j]是否是回文串
    bool isPalindrome(int i, int j)
    {
        while (i < j)
        {
            if (s[i] != s[j])
            {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};

// O(n^2) 动态规划
class Solution2
{
public:
    Solution2(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<bool>>(s.size(), vector<bool>(s.size()));
        book = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));

        // dp[i]表示将s[0]~s[i]切分成若干回文串所需的最少切分数
        vector<int> dp(s.size());

        dp[0] = 0;
        for (int i = 1; i < (int)s.size(); ++i)
        {
            dp[i] = dp[i - 1] + 1;
            for (int j = i - 1; j >= 0; --j)
            {
                if (isPalindrome(j, i))
                {
                    if (j > 0)
                    {
                        dp[i] = min(dp[i], dp[j - 1] + 1);
                    }
                    else
                    {
                        dp[i] = 0;
                    }
                }
            }
        }

        return dp.back();
    }

private:
    string s;
    vector<vector<bool>> cache, book;

    // 判断s[i]~s[j]是否是回文串
    bool isPalindrome(int i, int j)
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

        if (i + 1 == j)
        {
            return cache[i][j] = s[i] == s[j];
        }

        if (s[i] != s[j])
        {
            return false;
        }

        return cache[i][j] = isPalindrome(i + 1, j - 1);
    }
};

class Solution 
{
public:
    int minCut(string s) 
    {
        //return Solution1(s).solve();
        return Solution2(s).solve();
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"aab", 1},
        {"a", 0},
        {"ab", 1},
    };

    test(&Solution::minCut, cases);

	return 0;
}