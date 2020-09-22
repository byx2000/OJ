// https://leetcode-cn.com/problems/cherry-pickup/

#include "../common/common.h"

// O(n^4) ��̬�滮
class Solution1
{
public:
    Solution1(const vector<vector<int>>& nums)
        : nums(nums), n(nums.size()) {}

    int solve()
    {
        cache = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, -2))));
        int r = dp(n - 1, n - 1, n - 1, n - 1);
        return (r == -1) ? 0 : r;
    }

private:
    vector<vector<int>> nums;
    int n;
    vector<vector<vector<vector<int>>>> cache; // ��ά����

    // ��һ���˴�(0, 0)�ߵ�(i, j)���ڶ����˴�(0, 0)�ߵ�(k, l)
    // ���޷��������-1
    int dp(int i, int j, int k, int l)
    {
        // Խ��
        if (i < 0 || i >= n || j < 0 || j >= n || k < 0 || k >= n || l < 0 || l >= n) return -1;

        if (cache[i][j][k][l] != -2)
        {
            return cache[i][j][k][l];
        }

        // ���
        if (i == 0 && j == 0 && k == 0 && l == 0)
        {
            return cache[i][j][k][l] = nums[i][j];
        }

        // �޷�����
        if (nums[i][j] == -1 || nums[k][l] == -1) return -1;

        int r1 = dp(i - 1, j, k - 1, l);
        int r2 = dp(i - 1, j, k, l - 1);
        int r3 = dp(i, j - 1, k - 1, l);
        int r4 = dp(i, j - 1, k, l - 1);

        int ret = -1;
        if (r1 != -1) ret = max(ret, r1);
        if (r2 != -1) ret = max(ret, r2);
        if (r3 != -1) ret = max(ret, r3);
        if (r4 != -1) ret = max(ret, r4);

        if (ret == -1) return cache[i][j][k][l] = -1;

        if (i == k && j == l)
        {
            ret += nums[i][j];
        }
        else
        {
            ret += (nums[i][j] + nums[k][l]);
        }

        return cache[i][j][k][l] = ret;
    }
};

// O(n^3) ��̬�滮
class Solution2
{
public:
    Solution2(const vector<vector<int>>& nums)
        : nums(nums), n(nums.size()) {}

    int solve()
    {
        cache = vector<vector<vector<int>>>(n * 2, vector<vector<int>>(n, vector<int>(n, -2)));
        int r = dp(2 * n - 1, n - 1, n - 1);
        return (r == -1) ? 0 : r;
    }

private:
    vector<vector<int>> nums;
    int n;
    vector<vector<vector<int>>> cache; // ��ά����

    // ÿ���˶�����n������һ�����ڵ�i�У��ڶ������ڵ�k��
    // ���޷��������-1
    int dp(int n, int i, int k)
    {
        // ��������
        int j = n - i - 1;
        int l = n - k - 1;

        // Խ��
        if (i < 0 || i >= n || j < 0 || j >= n || k < 0 || k >= n || l < 0 || l >= n) return -1;

        if (cache[n][i][k] != -2)
        {
            return cache[n][i][k];
        }

        // ���
        if (i == 0 && j == 0 && k == 0 && l == 0)
        {
            return cache[n][i][k] = nums[i][j];
        }

        // �޷�����
        if (nums[i][j] == -1 || nums[k][l] == -1) return -1;

        int r1 = dp(n - 1, i - 1, k - 1);
        int r2 = dp(n - 1, i - 1, k);
        int r3 = dp(n - 1, i, k - 1);
        int r4 = dp(n - 1, i, k);

        int ret = -1;
        if (r1 != -1) ret = max(ret, r1);
        if (r2 != -1) ret = max(ret, r2);
        if (r3 != -1) ret = max(ret, r3);
        if (r4 != -1) ret = max(ret, r4);

        if (ret == -1) return cache[n][i][k] = -1;

        if (i == k && j == l)
        {
            ret += nums[i][j];
        }
        else
        {
            ret += (nums[i][j] + nums[k][l]);
        }

        return cache[n][i][k] = ret;
    }
};

class Solution 
{
public:
    int cherryPickup(vector<vector<int>>& nums) 
    {
        //return Solution1(nums).solve();
        return Solution2(nums).solve();
    }
};

int main()
{
    vector<vector<int>> nums
    {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1,  1},
    };
    TEST(Assert::areEqual(Solution().cherryPickup(nums), 5));

    nums = vector<vector<int>>
    {
        {1, 1, -1},
        {1, -1, 1},
        {-1, 1, 1},
    };
    TEST(Assert::areEqual(Solution().cherryPickup(nums), 0));

    nums = vector<vector<int>>
    {
        {1},
    };
    TEST(Assert::areEqual(Solution().cherryPickup(nums), 1));

	return 0;
}