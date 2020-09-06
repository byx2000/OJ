// https://leetcode-cn.com/problems/divisor-game/

#include "../common/common.h"

class Solution 
{
public:
    bool divisorGame(int n) 
    {
        cache = vector<int>(n + 1, -1);
        return dp(n);
    }

private:
    vector<int> cache;

    bool dp(int n)
    {
        if (cache[n] != -1)
        {
            return cache[n];
        }

        bool result = false;
        for (int i = 1; i < n; ++i)
        {
            if (n % i == 0)
            {
                result = result || (!dp(n - i));
            }
        }

        return cache[n] = result;
    }
};

int main()
{
    TEST(Assert::isTrue(Solution().divisorGame(2)));
    TEST(!Assert::isTrue(Solution().divisorGame(3)));

	return 0;
}