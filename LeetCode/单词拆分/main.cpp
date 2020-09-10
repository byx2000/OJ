// https://leetcode-cn.com/problems/word-break/

#include "../common/common.h"

// 区间dp 时间O(n^2) 空间O(n^2)
class Solution1
{
public:
    Solution1(const string& s, const vector<string>& words) :
        s(s), words(words) {}

    int solve()
    {
        for (string w : words)
        {
            dict[w] = false;
        }

        cache = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));
        book = vector<vector<bool>>(s.size(), vector<bool>(s.size(), false));

        return dp(0, s.size() - 1);
    }

private:
    string s;
    vector<string> words;
    unordered_map<string, bool> dict;
    vector<vector<bool>> cache, book;

    // s[i]~s[j]是否能被拆分
    bool dp(int i, int j)
    {
        if (book[i][j])
        {
            return cache[i][j];
        }
        book[i][j] = true;

        if (i == j)
        {
            return cache[i][j] = dict.count(string(1, s[i])) > 0;
        }

        bool ret = dict.count(s.substr(i, j - i + 1)) > 0;
        // 拆分成s[i]~s[k]和s[k + 1]~s[j]两段
        for (int k = i; k < j; ++k)
        {
            ret = ret || (dp(i, k) && dp(k + 1, j));
            if (ret)
            {
                return cache[i][j] = true;
            }
        }

        return cache[i][j] = false;
    }
};

// 一维dp 时间O(n^2) 空间O(n)
class Solution2
{
public:
    Solution2(const string& s, const vector<string>& words) :
        s(s), words(words) {}

    int solve()
    {
        for (string w : words)
        {
            dict[w] = false;
        }

        cache = vector<bool>(s.size(), false);
        book = vector<bool>(s.size(), false);

        return dp(s.size() - 1);
    }

private:
    string s;
    vector<string> words;
    unordered_map<string, bool> dict;
    vector<bool> cache, book;

    // s[0]~s[i]是否能被拆分
    bool dp(int i)
    {
        if (book[i])
        {
            return cache[i];
        }
        book[i] = true;

        if (i == 0)
        {
            return cache[i] = dict.count(string(1, s[0])) > 0;
        }

        bool ret = dict.count(s.substr(0, i + 1)) > 0;
        // 拆分成s[0]~s[j]和s[j + 1]~s[i]两段 
        for (int j = 0; j < i; ++j)
        {
            ret = ret || (dp(j) && dict.count(s.substr(j + 1, i - j)) > 0);
            if (ret)
            {
                return cache[i] = true;
            }
        }

        return cache[i] = false;
    }
};

class Solution 
{
public:
    bool wordBreak(string s, vector<string>& words) 
    {
        //return Solution1(s, words).solve();
        return Solution2(s, words).solve();
    }
};

int main()
{
    vector<string> words{ "leet", "code" };
    TEST(Assert::isTrue(Solution().wordBreak("leetcode", words)));

    words = vector<string>{ "apple", "pen" };
    TEST(Assert::isTrue(Solution().wordBreak("applepenapple", words)));

    words = vector<string>{ "cats", "dog", "sand", "and", "cat" };
    TEST(!Assert::isTrue(Solution().wordBreak("catsandog", words)));

    words = vector<string>{ "a" };
    TEST(Assert::isTrue(Solution().wordBreak("a", words)));

	return 0;
}