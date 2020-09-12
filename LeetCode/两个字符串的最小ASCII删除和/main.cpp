// https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const string& s1, const string& s2)
        : s1(s1), s2(s2) {}

    int solve()
    {
        cache = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));
        return dp(s1.size() - 1, s2.size() - 1);
    }

private:
    string s1, s2;
    vector<vector<int>> cache;

    // 让s1[0]~s1[i]和s2[0]~s2[j]相等需要删除的最少字符ASCII之和
    int dp(int i, int j)
    {
        if (i < 0)
        {
            return accumulate(s2.begin(), s2.begin() + j + 1, 0);
        }
        else if (j < 0)
        {
            return accumulate(s1.begin(), s1.begin() + i + 1, 0);
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
            return cache[i][j] = min(dp(i - 1, j) + s1[i], dp(i, j - 1) + s2[j]);
        }
    }
};

class Solution
{
public:
    int minimumDeleteSum(string s1, string s2)
    {
        return Solution1(s1, s2).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minimumDeleteSum("sea", "eat"), 231));
    TEST(Assert::areEqual(Solution().minimumDeleteSum("delete", "leet"), 403));

	return 0;
}