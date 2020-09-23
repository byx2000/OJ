// https://leetcode-cn.com/problems/minimum-distance-to-type-a-word-using-two-fingers/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const string& word) : word(word) {}

    int solve()
    {
        cache = vector<vector<vector<int>>>(word.size(), vector<vector<int>>('Z' + 1, vector<int>('Z' + 1, -1)));

        int result = numeric_limits<int>::max();
        for (char c1 = 'A'; c1 <= 'Z'; ++c1)
        {
            for (char c2 = 'A'; c2 <= 'Z'; ++c2)
            {
                result = min(result, dp(0, c1, c2));
            }
        }

        return result;
    }

private:
    string word;
    vector<vector<vector<int>>> cache;

    // 字符c1和字符c2的距离
    int dist(char c1, char c2)
    {
        int x1 = (c1 - 'A') / 6, y1 = (c1 - 'A') % 6;
        int x2 = (c2 - 'A') / 6, y2 = (c2 - 'A') % 6;
        return abs(x1 - x2) + abs(y1 - y2);
    }

    // 当前准备输入word[k]，左手在字符c1上，右手在字符c2上
    int dp(int k, char c1, char c2)
    {
        // 输入完毕
        if (k == word.size())
        {
            return 0;
        }

        if (cache[k][c1][c2] != -1)
        {
            return cache[k][c1][c2];
        }

        return cache[k][c1][c2] = min(dp(k + 1, word[k], c2) + dist(word[k], c1), dp(k + 1, c1, word[k]) + dist(word[k], c2));
    }
};

class Solution 
{
public:
    int minimumDistance(string word) 
    {
        return Solution1(word).solve();
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"CAKE", 3},
        {"HAPPY", 6},
        {"NEW", 3},
        {"YEAR", 7},
    };

    test(&Solution::minimumDistance, cases);

	return 0;
}