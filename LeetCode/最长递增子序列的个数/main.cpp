// https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/

#include "../common/common.h"

class Solution 
{
public:
    int findNumberOfLIS(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        vector<int> length(nums.size()), count(nums.size());

        length[0] = count[0] = 1;
        int maxLength = 1;
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            length[i] = 1;
            count[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    if (length[j] + 1 > length[i])
                    {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                    }
                    else if (length[j] + 1 == length[i])
                    {
                        count[i] += count[j];
                    }
                }
            }
            maxLength = max(maxLength, length[i]);
        }

        int result = 0;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            if (length[i] == maxLength)
            {
                result += count[i];
            }
        }

        return result;
    }
};

int main()
{
    Cases<vector<int>, int> cases
    {
        {{ 1,3,5,4,7 }, 2},
        {{ 2,2,2,2,2 }, 5},
        {{ 1,2,4,3,5,4,7,2 }, 3},
        {{ }, 0},
        {{ 1 }, 1},
    };

    test(&Solution::findNumberOfLIS, cases);

	return 0;
}