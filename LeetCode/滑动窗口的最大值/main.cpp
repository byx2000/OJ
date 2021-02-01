// https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/

#include "../common/common.h"

class Solution 
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        //return solution1(nums, k);
        return solution2(nums, k);
    }

private:
    vector<int> solution1(vector<int>& nums, int k)
    {
        if (nums.empty()) return {};

        vector<int> result;
        for (int i = 0; i + k - 1 < (int)nums.size(); ++i)
        {
            int maxVal = nums[i];
            for (int j = i + 1; j <= i + k - 1; ++j)
            {
                maxVal = max(maxVal, nums[j]);
            }
            result.push_back(maxVal);
        }
        return result;
    }

    vector<int> solution2(vector<int>& nums, int k)
    {
        if (nums.empty()) return {};

        // 获取第一个窗口的最大值
        int maxVal = nums[0];
        for (int i = 1; i < k; ++i)
        {
            maxVal = max(maxVal, nums[i]);
        }
        vector<int> result{ maxVal };

        // 从第二个窗口开始
        for (int i = 1; i + k - 1 < (int)nums.size(); ++i)
        {
            int out = nums[i - 1], in = nums[i + k - 1];
            int maxVal = result.back();
            // 最大值未被移出
            if (maxVal != out)
            {
                result.push_back(max(maxVal, in));
            }
            // 最大值被移除
            else
            {
                maxVal = nums[i];
                for (int j = i + 1; j <= i + k - 1; ++j)
                {
                    maxVal = max(maxVal, nums[j]);
                }
                result.push_back(maxVal);
            }
        }

        return result;
    }
};

int main()
{
    Cases<vector<int>, int, vector<int>> cases
    {
        {{}, 0, {}},
        {{1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}},
    };

    test(&Solution::maxSlidingWindow, cases);

	return 0;
}