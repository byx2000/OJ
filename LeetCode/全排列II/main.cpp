// https://leetcode-cn.com/problems/permutations-ii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums) : nums(nums) {}

    vector<vector<int>> solve()
    {
        book = vector<bool>(nums.size(), false);
        record = vector<int>(nums.size(), 0);
        res.clear();
        sort(nums.begin(), nums.end());
        dfs(0);
        return res;
    }

private:
    vector<int> nums;
    vector<bool> book;
    vector<int> record;
    vector<vector<int>> res;

    void dfs(int index)
    {
        if (index == nums.size())
        {
            res.push_back(record);
            return;
        }

        int last = 0;
        bool first = true;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            if (!book[i] && (last != nums[i] || first))
            {
                last = nums[i];
                first = false;
                book[i] = true;
                record[index] = nums[i];
                dfs(index + 1);
                book[i] = false;
            }
        }
    }
};

class Solution
{
public:
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        return Solution1(nums).solve();
    }
};

int main()
{
	return 0;
}