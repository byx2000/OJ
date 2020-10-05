// https://leetcode-cn.com/problems/combination-sum/

#include "../common/common.h"

class DFS
{
public:
    DFS(const vector<int>& nums, int target) : nums(nums), target(target) {}
    vector<vector<int>> solve()
    {
        res.clear();
        search(0, target);
        return res;
    }
private:
    vector<int> nums;
    int target;
    vector<int> record;
    vector<vector<int>> res;

    void search(int iNum, int sum)
    {
        if (sum == 0)
        {
            res.push_back(record);
            return;
        }

        if (iNum >= (int)nums.size())
        {
            return;
        }

        if (sum >= nums[iNum])
        {
            record.push_back(nums[iNum]);
            search(iNum, sum - nums[iNum]);
            record.pop_back();
        }

        search(iNum + 1, sum);
    }
};

class Solution
{
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        return DFS(candidates, target).solve();
    }
};

int main()
{
    Cases<vector<int>, int, vector<vector<int>>> cases
    {
        {{2,3,6,7}, 7, {{7}, {2, 2, 3}}},
        {{2,3,5}, 8, {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}}},
    };

    test(&Solution::combinationSum, cases, equivalent);

	return 0;
}