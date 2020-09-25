// https://leetcode-cn.com/problems/longest-chunked-palindrome-decomposition/

#include "../common/common.h"

// O(n^3) 动态规划
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
        return dp(0, s.size() - 1);
    }

private:
    string s;
    vector<vector<int>> cache;

    // s[i]~s[j]的最大回文段数
    int dp(int i, int j)
    {
        if (cache[i][j] != -1) return cache[i][j];
        if (i > j) return cache[i][j] = 0;
        if (i == j) return cache[i][j] = 1;
        if (i + 1 == j) return cache[i][j] = (s[i] == s[j]) ? 2 : 1;

        int ret = 1;
        for (int len = 1; len <= (j - i + 1) / 2; ++len)
        {
            string s1 = s.substr(i, len);
            string s2 = s.substr(j - len + 1, len);
            if (s1 == s2)
            {
                ret = max(ret, dp(i + len, j - len) + 2);
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
        return dp(0, s.size() - 1);
    }

private:
    string s;
    vector<vector<int>> cache;

    // s[i]~s[j]的最大回文段数
    int dp(int i, int j)
    {
        if (cache[i][j] != -1) return cache[i][j];
        if (i > j) return cache[i][j] = 0;
        if (i == j) return cache[i][j] = 1;
        if (i + 1 == j) return cache[i][j] = (s[i] == s[j]) ? 2 : 1;

        int ret = 1;
        for (int len = 1; len <= (j - i + 1) / 2; ++len)
        {
            string s1 = s.substr(i, len);
            string s2 = s.substr(j - len + 1, len);
            if (s1 == s2)
            {
                return cache[i][j] = dp(i + len, j - len) + 2;
            }
        }

        return cache[i][j] = ret;
    }
};

class Solution 
{
public:
    int longestDecomposition(string s) 
    {
        //return Solution1(s).solve();
        return Solution2(s).solve();
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"ghiabcdefhelloadamhelloabcdefghi", 7},
        {"merchant", 1},
        {"antaprezatepzapreanta", 11},
        {"aaa", 3},
    };

    test(&Solution::longestDecomposition, cases);

	return 0;
}