// https://www.luogu.com.cn/problem/P3052

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// ȫ���� + ��̬�滮
class Solution1
{
public:
    Solution1(const vector<int>& nums, int w)
        : nums(nums), w(w) {}

    int solve()
    {
        sort(nums.begin(), nums.end());
        prefixSum = vector<int>(nums.size());
        int res = nums.size();
        do
        {
            partial_sum(nums.begin(), nums.end(), prefixSum.begin());
            cache = vector<int>(nums.size(), -1);
            res = min(res, dp(nums.size() - 1));
        } while (next_permutation(nums.begin(), nums.end()));
        return res;
    }

private:
    vector<int> nums;
    int w;
    vector<int> prefixSum;
    vector<int> cache;

    // nums[i] + nums[i+1] + ... + nums[j]
    int sum(int i, int j)
    {
        return (i == 0) ? prefixSum[j] : prefixSum[j] - prefixSum[i - 1];
    }

    // ��nums[0]~nums[index]�ֳ������飬ʹÿ��ĺͲ�����w
    int dp(int index)
    {
        if (cache[index] != -1) return cache[index];

        if (index == 0) return cache[index] = (nums[0] <= w) ? 1 : 0;

        if (sum(0, index) <= w) return cache[index] = 1;

        int ret = dp(index - 1) + 1;
        for (int i = index - 1; i >= 1 && sum(i, index) <= w; --i)
        {
            ret = min(ret, dp(i - 1) + 1);
        }

        return cache[index] = ret;
    }
};

// ���ݷ�
// ��n����Ʒ�������ɸ������У�������Ҫ�õ�������
class Solution2
{
public:
    Solution2(const vector<int>& nums, int w)
        : nums(nums), w(w), minCnt(0) {}

    int solve()
    {
        minCnt = nums.size();
        dfs(0);
        return minCnt;
    }

private:
    vector<int> nums;
    vector<int> box;
    int w;
    int minCnt;

    // ��ǰ���ڷŵ�index����Ʒ
    // box.size()���ڵ�ǰ����������
    void dfs(int index)
    {
        // ��֦����ǰ�������������ڵ�ǰ��С������
        if ((int)box.size() >= minCnt) return;

        // ������Ʒ�������
        if (index == nums.size())
        {
            minCnt = min(minCnt, (int)box.size());
            return;
        }

        // ��һ�µ�ǰ��Ʒ�ܷ����ĸ�������
        for (int i = 0; i < (int)box.size(); ++i)
        {
            if (box[i] + nums[index] <= w)
            {
                box[i] += nums[index];
                dfs(index + 1);
                box[i] -= nums[index];
            }
        }

        // �¿�һ������
        box.push_back(nums[index]);
        dfs(index + 1);
        box.pop_back();
    }
};

int main()
{
    int n, w;
    cin >> n >> w;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    //cout << Solution1(nums, w).solve();
    cout << Solution2(nums, w).solve();

    return 0;
}