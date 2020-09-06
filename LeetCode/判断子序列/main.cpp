// https://leetcode-cn.com/problems/is-subsequence/

#include "../common/common.h"

// ½â·¨1£ºË«Ö¸Õë
class Solution1
{
public:
    Solution1(const string& s, const string& t)
        : s(s), t(t) {}

    bool solve()
    {
        int i = 0, j = 0;
        while (i < (int)s.size() && j < (int)t.size())
        {
            if (s[i] == t[j])
            {
                i++;
            }

            j++;
        }

        return i == s.size();
    }

private:
    string s, t;
};

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        return Solution1(s, t).solve();
    }
};

int main()
{
    TEST(Assert::isTrue(Solution().isSubsequence("abc", "ahbgdc")));
    TEST(!Assert::isTrue(Solution().isSubsequence("axc", "ahbgdc")));

	return 0;
}