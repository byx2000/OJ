// https://leetcode-cn.com/problems/number-of-ways-to-paint-n-x-3-grid/

#include "../common/common.h"

class Solution 
{
public:
    int numOfWays(int n)
    {
        static const int MOD = 1000000007;

        // x等于上一层ABA型的数量
        // y等于上一层ABC型的数量
        long long x = 6, y = 6;
        for (int i = 1; i < n; ++i)
        {
            long long tx = x, ty = y;
            x = ((3 * tx) % MOD + (2 * ty) % MOD) % MOD;
            y = ((2 * tx) % MOD + (2 * ty) % MOD) % MOD;
        }

        return (x + y) % MOD;
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().numOfWays(1), 12));
    TEST(Assert::areEqual(Solution().numOfWays(2), 54));
    TEST(Assert::areEqual(Solution().numOfWays(3), 246));
    TEST(Assert::areEqual(Solution().numOfWays(7), 106494));
    TEST(Assert::areEqual(Solution().numOfWays(5000), 30228214));

	return 0;
}