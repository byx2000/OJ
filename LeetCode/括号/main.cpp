// https://leetcode-cn.com/problems/bracket-lcci/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(int n) : n(n) {}

    vector<string> solve()
    {
        res.clear();
        s.clear();
        search(0, 0);
        return res;
    }

private:
    int n;
    vector<string> res;
    string s;

    void search(int nLeft, int nRight)
    {
        if (nLeft == n && nRight == n)
        {
            res.push_back(s);
            return;
        }

        if (nLeft > n || nRight > n || nLeft < nRight)
        {
            return;
        }

        s.push_back('(');
        search(nLeft + 1, nRight);
        s.pop_back();

        s.push_back(')');
        search(nLeft, nRight + 1);
        s.pop_back();
    }
};

class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        return Solution1(n).solve();
    }
};

int main()
{
	return 0;
}