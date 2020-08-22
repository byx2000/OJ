// https://leetcode-cn.com/problems/wildcard-matching/

#include "../common/common.h"

class Solution
{
    string s, p;
    int n, m;
    vector<vector<bool>> cache, book;

    bool cacheExist(int i, int j)
    {
        return book[i][j];
    }

    void addCache(int i, int j, bool val)
    {
        book[i][j] = true;
        cache[i][j] = val;
    }

    bool getCache(int i, int j)
    {
        return cache[i][j];
    }

    bool dp(int i, int j)
    {
        if (i >= n || j >= m)
        {
            if (i == n && j < m)
            {
                return p[j] == '*' && dp(i, j + 1);
            }
            return i == n && j == m;
        }

        if (cacheExist(i, j))
        {
            return getCache(i, j);
        }

        bool ret;
        if (p[j] == '?')
        {
            ret = dp(i + 1, j + 1);
        }
        else if (p[j] == '*')
        {
            ret = dp(i + 1, j) || dp(i, j + 1);
        }
        else
        {
            ret = s[i] == p[j] && dp(i + 1, j + 1);
        }

        addCache(i, j, ret);
        return ret;
    }

public:
    bool isMatch(string s, string p)
    {
        this->s = s;
        this->p = p;
        n = s.size();
        m = p.size();

        book = vector<vector<bool>>(n, vector<bool>(m, false));
        cache = vector<vector<bool>>(n, vector<bool>(m));

        return dp(0, 0);
    }
};

int main()
{
    assert(!Solution().isMatch("aa", "a"));
    assert(Solution().isMatch("aa", "*"));
    assert(!Solution().isMatch("cb", "?a"));
    assert(Solution().isMatch("adceb", "*a*b"));
    assert(!Solution().isMatch("acdcb", "a*c?b"));

	return 0;
}