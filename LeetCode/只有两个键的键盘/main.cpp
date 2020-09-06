// https://leetcode-cn.com/problems/2-keys-keyboard/

#include "../common/common.h"

// �ⷨ1����̬�滮
class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        cache = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));
        return dp(0, 1);
    }

private:
    int n;
    vector<vector<int>> cache;

    // ���а���k��A����ǰ��m��A������Ҫ�����ٲ�����
    int dp(int k, int m)
    {
        if (m == n)
        {
            return 0;
        }

        if (m > n)
        {
            return n + 1;
        }

        if (cache[k][m] != -1)
        {
            return cache[k][m];
        }

        int ret = dp(m, 2 * m) + 2; // ȫѡ��ճ��
        if (k > 0)
        {
            ret = min(ret, dp(k, m + k) + 1); // ճ��
        }

        return cache[k][m] = ret;
    }
};

class Solution
{
public:
    int minSteps(int n)
    {
        return Solution1(n).solve();
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minSteps(3), 3));
    TEST(Assert::areEqual(Solution().minSteps(10), 7));

    return 0;
}