// https://leetcode-cn.com/problems/search-a-2d-matrix/

#include "../common/common.h"

class Solution 
{
public:
    bool searchMatrix(vector<vector<int>>& mat, int target) 
    {
        int row = mat.size();
        int col = mat[0].size();
        int left = 0, right = row * col - 1;
        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            int r = mid / col;
            int c = mid % col;
            if (mat[r][c] == target) return true;
            else if (mat[r][c] < target) left = mid + 1;
            else right = mid - 1;
        }

        for (int i = left; i <= right; ++i)
        {
            int r = i / col;
            int c = i % col;
            if (mat[r][c] == target) return true;
        }

        return false;
    }
};

int main()
{
    Cases<vector<vector<int>>, int, bool> cases
    {
        {{{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 3, true},
        {{{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 13, false},
    };

    test(&Solution::searchMatrix, cases);

	return 0;
}