// https://leetcode-cn.com/problems/sparse-array-search-lcci/

#include "../common/common.h"

class Solution
{
public:
    int findString(vector<string>& words, string s)
    {
        // �ҵ���ߵ�һ����Ϊ�յ��ַ���
        int left = 0;
        while (left < (int)words.size() && words[left] == "") left++;

        // ��������ȫΪ���ַ���
        if (left == words.size()) return -1;

        // �ҵ��ұߵ�һ����Ϊ�յ��ַ���
        int right = words.size() - 1;
        while (right >= 0 && words[right] == "") right--;

        // ֻ��һ����Ϊ�յ��ַ���
        if (left == right) return (words[left] == s) ? left : -1;

        // ���ֲ���
        while (right - left > 3)
        {
            // �ҵ���Ϊ�յ��е�
            int mid = left + (right - left) / 2;
            int t = mid;
            while (mid >= left && words[mid] == "") mid--;

            // ����[left, mid]ȫΪ��
            if (mid < left) { left = t + 1; continue; }

            if (words[mid] == s) return mid;
            else if (words[mid] < s) left = mid + 1;
            else right = mid - 1;
        }

        for (int i = left; i <= right; ++i)
        {
            if (words[i] == s) return i;
        }

        return -1;
    }
};

int main()
{
    Cases<vector<string>, string, int> cases
    {
        {{"","",""}, "abc", -1},
        {{"at", "", "", "", "ball", "", "", "car", "", "","dad", "", ""}, "ta", -1},
        {{"at", "", "", "", "ball", "", "", "car", "", "","dad", "", ""}, "ball", 4},
    };

    test(&Solution::findString, cases);

	return 0;
}