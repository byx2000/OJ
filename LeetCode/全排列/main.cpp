// https://leetcode-cn.com/problems/permutations/

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

        for (int i = 0; i < (int)nums.size(); ++i)
        {
            if (!book[i])
            {
                book[i] = true;
                record[index] = nums[i];
                dfs(index + 1);
                book[i] = false;
            }
        }
    }
};

class Solution2
{
public:
    Solution2(const vector<int>& nums) : nums(nums) {}

    vector<vector<int>> solve()
    {
        res.clear();
        dfs(0);
        return res;
    }

private:
    vector<int> nums;
    vector<vector<int>> res;

    void dfs(int index)
    {
        if (index == nums.size())
        {
            res.push_back(nums);
            return;
        }

        for (int i = index; i < (int)nums.size(); ++i)
        {
            swap(nums[index], nums[i]);
            dfs(index + 1);
            swap(nums[index], nums[i]);
        }
    }
};

class Solution
{
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    return 0;
}