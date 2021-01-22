// https://leetcode-cn.com/problems/magic-index-lcci/

#include "../common/common.h"

class Solution 
{
public:
    int findMagicIndex(vector<int>& nums) 
    {
        int i = 0;
        while (i < (int)nums.size())
        {
            if (nums[i] == i) return i;
            if (nums[i] > i) i = nums[i];
            else i++;
        }
        return -1;
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{0, 2, 3, 4, 5}, 0},
        {{1, 1, 1}, 1},
    };

    test(&Solution::findMagicIndex, cases);

	return 0;
}