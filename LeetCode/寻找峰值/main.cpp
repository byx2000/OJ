// https://leetcode-cn.com/problems/find-peak-element/

#include "../common/common.h"

class Solution 
{
public:
    int findPeakElement(vector<int>& nums) 
    {
        int left = 0, right = nums.size() - 1;

        // ÿ��ѭ����ʼʱ��left���ڵ�λ��Ϊ�����¡���right���ڵ�λ��Ϊ�����¡�
        while (right - left > 3)
        {
            int mid = left + (right - left) / 2;
            // mid����λ��Ϊ�����¡���˵��mid��right֮��һ���С�ɽ�塱
            if (nums[mid] > nums[mid - 1]) left = mid;
            // ����˵��left��mid֮��һ���С�ɽ�塱
            else right = mid;
        }

        for (int i = left + 1; i <= right; ++i)
        {
            if (nums[i] < nums[i - 1]) return i - 1;
        }

        return right;
    }
};

int main()
{
    // �޲���

	return 0;
}