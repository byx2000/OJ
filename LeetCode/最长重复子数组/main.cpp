// https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/

#include "../common/common.h"

class Solution 
{
public:
    int findLength(vector<int>& A, vector<int>& B) 
    {
        this->A = A;
        this->B = B;
        cache = vector<vector<int>>(A.size() + 1, vector<int>(B.size() + 1, -1));

        int result = 0;
        for (int i = 0; i <= (int)A.size(); ++i)
        {
            for (int j = 0; j <= (int)B.size(); ++j)
            {
                result = max(result, dp(i, j));
            }
        }

        return result;
    }

private:
    vector<int> A, B;
    vector<vector<int>> cache;

    int dp(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return 0;
        }

        if (cache[i][j] != -1)
        {
            return cache[i][j];
        }

        if (A[i - 1] != B[j - 1])
        {
            return cache[i][j] = 0;
        }

        return cache[i][j] = dp(i - 1, j - 1) + 1;
    }
};

int main()
{
    vector<int> A{ 1,2,3,2,1 };
    vector<int> B{ 3,2,1,4,7 };
    TEST(Assert::areEqual(Solution().findLength(A, B), 3));

	return 0;
}