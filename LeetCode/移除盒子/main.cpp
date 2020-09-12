// https://leetcode-cn.com/problems/remove-boxes/

#include "../common/common.h"

class Solution 
{
public:
    int removeBoxes(vector<int>& nums) 
    {
        return 0;
    }
};

int main()
{
    vector<int> nums{ 1,3,2,2,2,3,4,3,1 };
    TEST(Assert::areEqual(Solution().removeBoxes(nums), 23));

	return 0;
}