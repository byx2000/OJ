// https://leetcode-cn.com/problems/video-stitching/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<vector<int>>& clips, int T)
        : clips(clips), T(T) {}

    int solve()
    {
        // 所有片段按结束时间排序
        sort(clips.begin(), clips.end(), [](auto a, auto b)
            {
                return a[1] < b[1];
            });

        cache = vector<vector<int>>(T + 1, vector<int>(clips.size(), -2));

        return dp(T, clips.size() - 1);
    }

private:
    vector<vector<int>> clips;
    int T;
    vector<vector<int>> cache;

    // 用clips[0]~clips[i]覆盖区间[0, t]所需片段的最小数目
    // 如果无法覆盖，则返回-1
    int dp(int t, int i)
    {
        if (cache[t][i] != -2)
        {
            return cache[t][i];
        }

        if (t == 0)
        {
            return cache[t][i] = 0;
        }

        if (i == 0)
        {
            if (clips[0][0] > 0 || clips[0][1] < t)
            {
                return cache[t][i] = -1;
            }
            return cache[t][i] = 1;
        }

        if (t > clips[i][1])
        {
            return cache[t][i] = -1;
        }

        if (t <= clips[i][0])
        {
            return cache[t][i] = dp(t, i - 1);
        }

        int r1 = dp(t, i - 1);
        int r2 = dp(clips[i][0], i - 1);

        if (r1 == -1 && r2 == -1)
        {
            return cache[t][i] = -1;
        }
        else if (r1 == -1)
        {
            return cache[t][i] = r2 + 1;
        }
        else if (r2 == -1)
        {
            return cache[t][i] = r1;
        }
        else
        {
            return cache[t][i] = min(r1, r2 + 1);
        }
    }
};

class Solution 
{
public:
    int videoStitching(vector<vector<int>>& clips, int T) 
    {
        return Solution1(clips, T).solve();
    }
};

int main()
{
    vector<vector<int>> clips{ {0,3} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 3), 1));

    clips = vector<vector<int>>{ {0,3},{3,5} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 5), 2));

    clips = vector<vector<int>>{ {0,1},{1,2} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 5), -1));

    clips = vector<vector<int>>{ {0,2},{0,3} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 3), 1));

    clips = vector<vector<int>>{ {0,2},{4,6},{8,10},{1,9},{1,5},{5,9} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 10), 3));

    clips = vector<vector<int>>{ {0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 9), 3));

    clips = vector<vector<int>>{ {0,4},{2,8} };
    TEST(Assert::areEqual(Solution().videoStitching(clips, 5), 2));

	return 0;
}