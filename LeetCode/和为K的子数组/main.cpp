// https://leetcode-cn.com/problems/subarray-sum-equals-k/

#include "../common/common.h"

// O(n^2)
class Solution1
{
public:
    Solution1(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        int count = 0;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            int sum = 0;
            for (int j = i; j >= 0; --j)
            {
                sum += nums[j];
                if (sum == k)
                {
                    count++;
                }
            }
        }

        return count;
    }

private:
    vector<int> nums;
    int k;
};

// O(n) 前缀和、哈希优化
class Solution2
{
public:
    Solution2(const vector<int>& nums, int k)
        : nums(nums), k(k) {}

    int solve()
    {
        int sum = 0;
        unordered_map<int, int> hash;
        hash[0] = 1;
        int count = 0;

        for (int i = 0; i < (int)nums.size(); ++i)
        {
            sum += nums[i];
            if (hash.count(sum - k) > 0)
            {
                count += hash[sum - k];
            }
            hash[sum]++;
        }

        return count;
    }

private:
    vector<int> nums;
    int k;
};

class Solution 
{
public:
    int subarraySum(vector<int>& nums, int k) 
    {
        //return Solution1(nums, k).solve();
        return Solution2(nums, k).solve();
    }
};

int main()
{
    vector<int> nums{ 1,1,1 };
    TEST(Assert::areEqual(Solution().subarraySum(nums, 2), 2));

    nums = vector<int>{ 1, 2, 3 };
    TEST(Assert::areEqual(Solution().subarraySum(nums, 3), 2));

	return 0;
}