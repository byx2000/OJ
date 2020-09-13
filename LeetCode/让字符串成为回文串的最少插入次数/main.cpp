// https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

#include "../common/common.h"

class Solution 
{
public:
    int minInsertions(string s) 
    {
        return 0;
    }
};

int main()
{
    TEST(Assert::areEqual(Solution().minInsertions("g"), 0));
    TEST(Assert::areEqual(Solution().minInsertions("no"), 1));
    TEST(Assert::areEqual(Solution().minInsertions("zzazz"), 0));
    TEST(Assert::areEqual(Solution().minInsertions("mbadm"), 2));
    TEST(Assert::areEqual(Solution().minInsertions("leetcode"), 5));

	return 0;
}