// https://leetcode-cn.com/problems/delete-operation-for-two-strings/

#include "../common/common.h"

// 解法1：转化为最长公共子序列
class Solution1
{
public:
    Solution1(const string& s1, const string& s2)
        : s1(s1), s2(s2) {}

    int solve()
    {
        cache = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));
        return s1.size() + s2.size() - 2 * dp(s1.size() - 1, s2.size() - 1);
    }

private:
    string s1, s2;
    vector<vector<int>> cache;

    // s1[0]~s1[i]和s2[0]~s2[j]的最长公共子序列长度
    int dp(int i, int j)
    {
        if (i < 0 || j < 0)
        {
            return 0;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (s1[i] == s2[j])
        {
            return cache[i][j] = dp(i - 1, j - 1) + 1;
        }
        else
        {
            return cache[i][j] = max(dp(i, j - 1), dp(i - 1, j));
        }
    }
};

// 解法2：直接dp
class Solution2
{
public:
    Solution2(const string& s1, const string& s2)
        : s1(s1), s2(s2) {}

    int solve()
    {
        cache = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));
        return dp(s1.size() - 1, s2.size() - 1);
    }

private:
    string s1, s2;
    vector<vector<int>> cache;

    // 让s1[0]~s1[i]和s2[0]~s2[j]相等需要删除的最少字符数
    int dp(int i, int j)
    {
        if (i < 0)
        {
            return j + 1;
        }
        else if (j < 0)
        {
            return i + 1;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (s1[i] == s2[j])
        {
            return cache[i][j] = dp(i - 1, j - 1);
        }
        else
        {
            return cache[i][j] = min(dp(i - 1, j), dp(i, j - 1)) + 1;
        }
    }
};

class Solution 
{
public:
    int minDistance(string s1, string s2)
    {
        //return Solution1(s1, s2).solve();
        return Solution2(s1, s2).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minDistance("a", ""), 1));
    TEST(Assert::areEqual(Solution().minDistance("", "ab"), 2));
    TEST(Assert::areEqual(Solution().minDistance("a", "b"), 2));
    TEST(Assert::areEqual(Solution().minDistance("ab", "a"), 1));
    TEST(Assert::areEqual(Solution().minDistance("sea", "eat"), 2));

	return 0;
}