// https://leetcode-cn.com/problems/sparse-array-search-lcci/

#include "../common/common.h"

class Solution
{
public:
    int findString(vector<string>& words, string s)
    {
        // 找到左边第一个不为空的字符串
        int left = 0;
        while (left < (int)words.size() && words[left] == "") left++;

        // 整个数组全为空字符串
        if (left == words.size()) return -1;

        // 找到右边第一个不为空的字符串
        int right = words.size() - 1;
        while (right >= 0 && words[right] == "") right--;

        // 只有一个不为空的字符串
        if (left == right) return (words[left] == s) ? left : -1;

        // 二分查找
        while (right - left > 3)
        {
            // 找到不为空的中点
            int mid = left + (right - left) / 2;
            int t = mid;
            while (mid >= left && words[mid] == "") mid--;

            // 区间[left, mid]全为空
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