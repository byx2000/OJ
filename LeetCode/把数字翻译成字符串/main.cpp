// https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/

#include "../common/common.h"

class Solution
{
    int dp(const string& num, int index)
    {
        if (index == num.size())
        {
            return 1;
        }

        if (index + 1 == num.size())
        {
            return 1;
        }

        int a = num[index] - '0';
        int b = num[index + 1] - '0';
        if (a == 0)
        {
            return dp(num, index + 1);
        }
        else if (a * 10 + b > 25)
        {
            return dp(num, index + 1);
        }
        else
        {
            return dp(num, index + 1) + dp(num, index + 2);
        }
    }

public:
    int translateNum(int num)
    {
        return dp(to_string(num), 0);
    }
};

int main()
{
    Cases<int, int> cases
    {
        {12258, 5},
    };

    test(&Solution::translateNum, cases);

	return 0;
}