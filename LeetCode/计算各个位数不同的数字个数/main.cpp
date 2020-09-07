// https://leetcode-cn.com/problems/count-numbers-with-unique-digits/

#include "../common/common.h"

class Solution 
{
public:
	int countNumbersWithUniqueDigits(int n) 
	{
		if (n == 0)
		{
			return 1;
		}

		int result = 10;
		int m = 9;
		for (int i = 0; i < n - 1; ++i)
		{
			m *= (9 - i);
			result += m;
		}

		return result;
	}
};

int main()
{
	TEST(Assert::areEqual(Solution().countNumbersWithUniqueDigits(2), 91));

	return 0;
}