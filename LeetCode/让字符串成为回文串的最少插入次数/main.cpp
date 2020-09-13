// https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

#include "../common/common.h"

// ת��Ϊ�����������
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        cache = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
        return s.size() - dp(0, s.size() - 1);
    }

private:
    string s;
    vector<vector<int>> cache;

    // s[i]~s[j]������������г���
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

// ֱ�Ӷ�̬�滮
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

    // ���Ӵ�s[i]~s[j]��ɻ��Ĵ������ٲ������
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
            return cache[i][j] = 0;
        }

        if (s[i] == s[j])
        {
            return cache[i][j] = dp(i + 1, j - 1);
        }
        else
        {
            return cache[i][j] = min(dp(i + 1, j), dp(i, j - 1)) + 1;
        }
    }
};

class Solution 
{
public:
    int minInsertions(string s) 
    {
        //return Solution1(s).solve();
        return Solution2(s).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minInsertions("g"), 0));
    TEST(Assert::areEqual(Solution().minInsertions("no"), 1));
    TEST(Assert::areEqual(Solution().minInsertions("zzazz"), 0));
    TEST(Assert::areEqual(Solution().minInsertions("mbadm"), 2));
    TEST(Assert::areEqual(Solution().minInsertions("leetcode"), 5));

	return 0;
}