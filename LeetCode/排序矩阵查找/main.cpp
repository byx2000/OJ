// https://leetcode-cn.com/problems/sorted-matrix-search-lcci/

#include "../common/common.h"

class Solution 
{
public:
    bool searchMatrix(vector<vector<int>>& mat, int target) 
    {
        for (int i = 0; i < (int)mat.size(); ++i)
        {
            int left = 0, right = mat[i].size() - 1;
            while (right - left > 3)
            {
                int mid = left + (right - left) / 2;
                if (mat[i][mid] == target) return true;
                else if (mat[i][mid] > target) right = mid - 1;
                else left = mid + 1;
            }

            for (int j = left; j <= right; ++j)
            {
                if (mat[i][j] == target) return true;
            }
        }

        return false;
    }
};

int main()
{
    Cases<vector<vector<int>>, int, bool> cases
    {
        {{
          {1,   4,  7, 11, 15},
          {2,   5,  8, 12, 19},
          {3,   6,  9, 16, 22},
          {10, 13, 14, 17, 24},
          {18, 21, 23, 26, 30}
        }, 5, true},
        {{
          {1,   4,  7, 11, 15},
          {2,   5,  8, 12, 19},
          {3,   6,  9, 16, 22},
          {10, 13, 14, 17, 24},
          {18, 21, 23, 26, 30}
        }, 20, false},
    };

    test(&Solution::searchMatrix, cases);

	return 0;
}