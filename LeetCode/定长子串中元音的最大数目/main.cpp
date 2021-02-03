// https://leetcode-cn.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/

#include "../common/common.h"

class Solution 
{
public:
    int maxVowels(string s, int k) 
    {
        //return solution1(s, k);
        return solution2(s, k);
    }
private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    // 暴力法
    int solution1(string s, int k)
    {
        int maxCount = 0;
        for (int i = 0; i + k - 1 < (int)s.size(); ++i)
        {
            int count = 0;
            for (int j = i; j <= i + k - 1; ++j)
            {
                if (isVowel(s[j])) count++;
            }
            maxCount = max(maxCount, count);
        }
        return maxCount;
    }

    // 滑动窗口
    int solution2(string s, int k)
    {
        int maxCount = 0;

        // 计算第一个窗口的元音数
        for (int i = 0; i < k; ++i)
        {
            if (isVowel(s[i])) maxCount++;
        }

        // 计算剩余窗口的元音数
        int count = maxCount;
        for (int i = 1; i + k - 1 < (int)s.size(); ++i)
        {
            char out = s[i - 1], in = s[i + k - 1];
            if (isVowel(out) && !isVowel(in)) count--;
            else if (!isVowel(out) && isVowel(in)) count++;
            maxCount = max(maxCount, count);
        }

        return maxCount;
    }
};

int main()
{
    Cases<string, int, int> cases
    {
        {"abciiidef", 3, 3},
        {"aeiou", 2, 2},
        {"leetcode", 3, 2},
        {"rhythms", 4, 0},
        {"tryhard", 4, 1},
    };

    test(&Solution::maxVowels, cases);

	return 0;
}