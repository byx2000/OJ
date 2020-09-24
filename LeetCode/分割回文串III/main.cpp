// https://leetcode-cn.com/problems/palindrome-partitioning-iii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const string& s, int k)
        : s(s), k(k) {}

    int solve()
    {
        cache1 = vector<vector<int>>(s.size(), vector<int>(s.size(), -1));
        cache2 = vector<vector<int>>(s.size(), vector<int>(k + 1, -1));
        return dp(s.size() - 1, k);
    }

private:
    string s;
    int k;
    vector<vector<int>> cache1, cache2;

    // 将s[i]~s[j]修改为回文串的最少修改次数
    int minChange(int i, int j)
    {
        if (cache1[i][j] != -1) return cache1[i][j];
        if (i == j) return cache1[i][j] = 0;
        if (i + 1 == j) return cache1[i][j] = (s[i] == s[j]) ? 0 : 1;
        if (s[i] == s[j]) return cache1[i][j] = minChange(i + 1, j - 1);
        return cache1[i][j] = minChange(i + 1, j - 1) + 1;
    }

    // 将s[0]~s[index]分成c份，使每份为回文串的最少修改次数
    // 假设 index + 1 >= c 且 c >= 1
    int dp(int index, int c)
    {
        if (cache2[index][c] != -1) return cache2[index][c];
        if (c == 1) return cache2[index][c] = minChange(0, index);
        int ret = dp(index - 1, c - 1);
        for (int i = index - 1; i >= c - 1 && i >= 1; --i)
        {
            ret = min(ret, dp(i - 1, c - 1) + minChange(i, index));
        }
        return cache2[index][c] = ret;
    }
};

class Solution 
{
public:
    int palindromePartition(string s, int k) 
    {
        return Solution1(s, k).solve();
    }
};

int main()
{
    Cases<string, int, int> cases
    {
        {"abc", 2, 1},
        {"aabbc", 3, 0},
        {"leetcode", 8, 0},
        {"tcymekt", 4, 2},
    };

    test(&Solution::palindromePartition, cases);

	return 0;
}