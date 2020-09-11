// https://leetcode-cn.com/problems/largest-sum-of-averages/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    double solve()
    {
        prefix = vector<double>(nums.size());
        partial_sum(nums.begin(), nums.end(), prefix.begin());
        cache = vector<vector<double>>(nums.size(), vector<double>(k + 1, -1));
        return dp(nums.size() - 1, k);
    }

private:
    vector<int> nums;
    int k;
    vector<double> prefix;
    vector<vector<double>> cache;

    // nums[0]~nums[i]分成k份的最大平均值和
    double dp(int i, int k)
    {
        // 保证i + 1 >= k
        
        if (cache[i][k] > 0)
        {
            return cache[i][k];
        }


        if (i + 1 == k)
        {
            return cache[i][k] = prefix[i];
        }

        if (k == 1)
        {
            return cache[i][k] = prefix[i] / (i + 1.0);
        }

        double ret = -1;
        for (int j = k - 2; j < i; ++j)
        {
            ret = max(ret, dp(j, k - 1) + (prefix[i] - prefix[j]) / ((double)i - j));
        }

        return cache[i][k] = ret;
    }
};

class Solution 
{
public:
    double largestSumOfAverages(vector<int>& nums, int k) 
    {
        return Solution1(nums, k).solve();
    }
};

int main()
{
    vector<int> nums{ 9,1,2,3,9 };
    TEST(Assert::areEqual(Solution().largestSumOfAverages(nums, 3), 20.0));

	return 0;
}