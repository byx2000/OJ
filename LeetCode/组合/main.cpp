// https://leetcode-cn.com/problems/combinations/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int k) : nums(nums), k(k) {}

    vector<vector<int>> solve()
    {
        res.clear();
        selected = vector<bool>(nums.size(), false);
        record = vector<int>(k);
        lastIndex = 0;
        dfs(0);
        return res;
    }

private:
    vector<int> nums;
    int k;
    vector<vector<int>> res;
    vector<bool> selected;
    vector<int> record;
    int lastIndex;

    void dfs(int index)
    {
        if (index == k)
        {
            res.push_back(record);
            return;
        }

        for (int i = lastIndex; i < (int)nums.size(); ++i)
        {
            if (!selected[i])
            {
                selected[i] = true;
                record[index] = nums[i];
                lastIndex = i + 1;
                dfs(index + 1);
                selected[i] = false;
            }
        }
    }
};

class Solution
{
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<int> nums(n);
        for (int i = 1; i <= n; ++i)
        {
            nums[i - 1] = i;
        }
        return Solution1(nums, k).solve();
    }
};

int main()
{
    vector<vector<int>> output
    {
        {2, 4},
        {3, 4},
        {2, 3},
        {1, 2},
        {1, 3},
        {1, 4},
    };
    TEST(Assert::areEquivalent(Solution().combine(4, 2), output));

	return 0;
}