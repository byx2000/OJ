// https://leetcode-cn.com/problems/longest-string-chain/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<string>& words) : words(words) {}

    int solve()
    {
        sort(words.begin(), words.end(), [](auto a, auto b)
            {
                return a.size() < b.size();
            });

        for (int i = 0; i < (int)words.size(); ++i)
        {
            index[words[i]] = i;
        }

        cache = vector<int>(words.size(), -1);

        int result = 1;
        for (int i = 0; i < (int)words.size(); ++i)
        {
            result = max(result, dp(i));
        }

        return result;
    }

private:
    vector<string> words;
    unordered_map<string, int> index;
    vector<int> cache;

    // 以words[i]结尾的单词链最大长度
    int dp(int i)
    {
        if (cache[i] != -1)
        {
            return cache[i];
        }

        if (words[i].size() == 1)
        {
            return cache[i] = 1;
        }

        int ret = 1;
        for (int j = 0; j < (int)words[i].size(); ++j)
        {
            string t = words[i];
            t.erase(t.begin() + j);
            if (index.count(t) > 0)
            {
                ret = max(ret, dp(index[t]) + 1);
            }
        }

        return cache[i] = ret;
    }
};

class Solution 
{
public:
    int longestStrChain(vector<string>& words) 
    {
        return Solution1(words).solve();
    }
};

int main()
{
    vector<string> words{ "a","b","ba","bca","bda","bdca" };
    TEST(Assert::areEqual(Solution().longestStrChain(words), 4));

	return 0;
}