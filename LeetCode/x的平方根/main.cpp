// https://leetcode-cn.com/problems/sqrtx/

#include "../common/common.h"

// ¶þ·Ö·¨ 
class Solution 
{
public:
	int mySqrt(int x) 
	{
		int left = 0, right = x;
		while (right - left > 3)
		{
			long long mid = left + (right - left) / 2;
			if (mid * mid == x) return mid;
			else if (mid * mid < x) left = mid;
			else right = mid - 1;
		}

		for (int i = left; i <= right; ++i)
		{
			if (i * i == x) return i;
			else if (i * i > x) return i - 1;
		}

		return right;
	}
};

int main()
{
	TEST(Assert::areEqual(Solution().mySqrt(0), 0));
	TEST(Assert::areEqual(Solution().mySqrt(1), 1));
	TEST(Assert::areEqual(Solution().mySqrt(4), 2));
	TEST(Assert::areEqual(Solution().mySqrt(6), 2));
	TEST(Assert::areEqual(Solution().mySqrt(8), 2));
	return 0;
}