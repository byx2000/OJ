// https://leetcode-cn.com/problems/sort-colors/

#include "../common/common.h"

class Solution 
{
public:
    void sortColors(vector<int>& nums)
    {
        int i = 0, j = nums.size() - 1, k = 0;
        while (1)
        {
            if (k > j)
            {
                break;
            }

            if (nums[k] == 0)
            {
                swap(nums[i], nums[k]);
                i++;
                k = i;
            }
            else if (nums[k] == 2)
            {
                swap(nums[j], nums[k]);
                j--;
            }
            else
            {
                k++;
            }
        }
    }
};

int main()
{
	return 0;
}