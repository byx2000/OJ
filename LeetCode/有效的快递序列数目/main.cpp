// https://leetcode-cn.com/problems/count-all-valid-pickup-and-delivery-options/

#include "../common/common.h"

class Solution
{
public:
    int countOrders(int n)
    {
        long a = 1;
        int MOD = 1000000007;
        for (long i = 1; i < n; ++i)
        {
            a = ((a * (2 * i + 1)) % MOD * (i + 1)) % MOD;
        }

        return (int)a;
    }
};

int main()
{
    Cases<int, int> cases
    {
        {1, 1},
        {2, 6},
        {3, 90},
    };

    test(&Solution::countOrders, cases);

	return 0;
}