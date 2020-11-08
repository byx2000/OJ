// https://leetcode-cn.com/problems/first-bad-version/

#include "../common/common.h"

bool isBadVersion(int version) { return false; }

class Solution
{
public:
    int firstBadVersion(int n)
    {
        int low = 1, high = n;

        while (high - low > 3)
        {
            int mid = low + (high - low) / 2; // 此处不能写 int mid = (low + high) / 2 ，为防止溢出
            if (isBadVersion(mid)) high = mid;
            else low = mid + 1;
        }

        for (int i = low; i <= high; ++i)
        {
            if (isBadVersion(i)) return i;
        }

        return -1;
    }
};

int main()
{
	// 无测试

	return 0;
}