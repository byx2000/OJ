// https://leetcode-cn.com/problems/gray-code/

#include "../common/common.h"

class Solution
{
    int powOf2(int n)
    {
        int r = 1;
        while (n--)
        {
            r *= 2;
        }
        return r;
    }

public:
    vector<int> grayCode(int n)
    {
        if (n == 0)
        {
            return vector<int> { 0 };
        }

        vector<int> res = grayCode(n - 1);
        for (int i = (int)res.size() - 1; i >= 0; --i)
        {
            res.push_back(res[i] + powOf2(n - 1));
        }

        return res;
    }
};

int main()
{
    Cases<int, vector<int>> cases
    {
        {1, {0, 1}},
        {2, {0, 1, 3, 2}},
        {3, {0, 1, 3, 2, 6, 7, 5, 4}},
    };

    test(&Solution::grayCode, cases);

    return 0;
}