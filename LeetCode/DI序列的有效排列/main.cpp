// https://leetcode-cn.com/problems/valid-permutations-for-di-sequence/

#include "../common/common.h"

// dfs
class Solution1
{
public:
    Solution1(const string& s) : s(s) {}

    int solve()
    {
        book = vector<bool>(s.size() + 1);
        int cnt = 0;
        for (int i = 0; i <= (int)s.size(); ++i)
        {
            book[i] = true;
            cnt += dfs(0, i);
            book[i] = false;
        }
        return cnt;
    }

private:
    string s;
    vector<bool> book;

    int dfs(int index, int last)
    {
        if (index == (int)s.size()) return 1;
        int lower = (s[index] == 'D') ? 0 : last + 1;
        int upper = (s[index] == 'D') ? last - 1 : s.size();
        int cnt = 0;
        for (int i = lower; i <= upper; ++i)
        {
            if (!book[i])
            {
                book[i] = true;
                cnt += dfs(index + 1, i);
                book[i] = false;
            }
        }
        return cnt;
    }
};

class Solution
{
public:
    int numPermsDISequence(string s)
    {
        return Solution1(s).solve();
    }
};

int main()
{
    Cases<string, int> cases
    {
        {"DID", 5},
    };

    test(&Solution::numPermsDISequence, cases);

    return 0;
}