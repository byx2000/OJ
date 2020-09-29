// https://loj.ac/problem/10164

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ±©Á¦
class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        int cnt = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (i < 10)
            {
                cnt++;
                continue;
            }

            int t = i;
            bool flag = true;
            int last = t % 10;
            t /= 10;
            while (t)
            {
                if (t % 10 > last)
                {
                    flag = false;
                    break;
                }
                last = t % 10;
                t /= 10;
            }

            if (flag) cnt++;
        }

        return cnt;
    }

private:
    int n;
};

// ÊýÎ»dp
class Solution2
{
public:
    Solution2(int n) : n(n) {}

    int solve()
    {
        digits = getDigits(n);
        cache = vector<vector<vector<int>>>(digits.size() + 1, vector<vector<int>>(10, vector<int>(2, -1)));
        return dp(0, 0, true);
    }

private:
    int n;
    vector<int> digits;
    vector<vector<vector<int>>> cache;

    vector<int> getDigits(int n)
    {
        vector<int> v;
        while (n)
        {
            v.push_back(n % 10);
            n /= 10;
        }
        reverse(v.begin(), v.end());
        return v;
    }

    int dp(int index, int last, bool top)
    {
        if (cache[index][last][top] != -1) return cache[index][last][top];
        if (index == (int)digits.size()) return cache[index][last][top] = 1;
        int upper = top ? digits[index] : 9;
        int cnt = 0;
        for (int i = last; i <= upper; ++i)
        {
            cnt += dp(index + 1, i, top && i == digits[index]);
        }
        return cache[index][last][top] = cnt;
    }
};

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        //cout << Solution1(b).solve() - Solution1(a - 1).solve() << endl;
        cout << Solution2(b).solve() - Solution2(a - 1).solve() << endl;
    }

    return 0;
}