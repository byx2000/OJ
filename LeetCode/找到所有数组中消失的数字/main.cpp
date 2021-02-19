// https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/

#include "../common/common.h"

class Solution 
{
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) 
    {
        //return solution1(nums);
        return solution2(nums);
    }

    // O(n) 使用额外空间
    vector<int> solution1(const vector<int>& nums)
    {
        vector<bool> book(nums.size() + 1, false);
        for (int n : nums)
        {
            book[n] = true;
        }

        vector<int> res;
        for (int i = 1; i <= (int)nums.size(); ++i)
        {
            if (!book[i]) res.push_back(i);
        }

        return res;
    }

    // O(n) 不使用额外空间
    vector<int> solution2(vector<int>& nums)
    {
        int n = nums.size();
        for (int x : nums)
        {
            nums[(x - 1) % n] += n;
        }

        vector<int> res;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] <= n) res.push_back(i + 1);
        }

        return res;
    }
};

int main()
{
    Cases<vector<int>, vector<int>> cases
    {
        {{4,3,2,7,8,2,3,1}, {5,6}},
    };

    test(&Solution::findDisappearedNumbers, cases);

	return 0;
}