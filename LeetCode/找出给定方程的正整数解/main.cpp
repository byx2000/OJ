// https://leetcode-cn.com/problems/find-positive-integer-solution-for-a-given-equation/

#include "../common/common.h"

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class CustomFunction
{
public:
    virtual int f(int x, int y) = 0;
    virtual ~CustomFunction() {}
};

class Solution
{
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z)
    {
        vector<vector<int>> result;
        for (int x = 1; x <= 1000; ++x)
        {
            int left = 1, right = 1000;
            bool find = false;
            while (right - left > 3)
            {
                int mid = left + (right - left) / 2;
                int val = customfunction.f(x, mid);
                if (val == z)
                {
                    result.push_back({ x, mid });
                    find = true;
                    break;
                }
                else if (val > z)
                    right = mid - 1;
                else
                    left = mid + 1;
            }

            if (!find)
            {
                for (int i = left; i <= right; ++i)
                {
                    if (customfunction.f(x, i) == z)
                    {
                        result.push_back({ x, i });
                        break;
                    }
                }
            }
        }
        return result;
    }
};

int main()
{
    // ÎÞ²âÊÔ

	return 0;
}