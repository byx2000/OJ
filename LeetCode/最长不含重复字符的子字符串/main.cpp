// https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/

#include "../common/common.h"

class Solution 
{
public:
    int lengthOfLongestSubstring(string s) 
    {
        //return solution1(s);
        return solution2(s);
    }

private:
    int solution1(const string& s)
    {
        int maxLen = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            set<char> set{ s[i] };
            int len = 1;
            for (int j = i + 1; j < (int)s.size(); ++j)
            {
                if (set.count(s[j]) == 0)
                {
                    set.insert(s[j]);
                    len++;
                }
                else break;
            }
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }

    int solution2(const string& s)
    {
        int maxLen = 0;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            vector<bool> table(256, false);
            table[s[i]] = true;
            int len = 1;
            for (int j = i + 1; j < (int)s.size(); ++j)
            {
                if (!table[s[j]])
                {
                    table[s[j]] = true;
                    len++;
                }
                else break;
            }
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"", 0},
        {"abcabcbb", 3},
        {"bbbbb", 1},
        {"pwwkew", 3},
    };

    test(&Solution::lengthOfLongestSubstring, cases);

	return 0;
}