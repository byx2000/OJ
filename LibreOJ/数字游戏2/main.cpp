// https://loj.ac/problem/10166

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ±©Á¦
class Solution1
{
public:
    Solution1(int n, int m) : n(n), m(m) {}

    int solve()
    {
        int cnt = 0;
        for (int i = 0; i <= n; ++i)
        {
            int t = i;
            int s = 0;
            while (t)
            {
                s += t % 10;
                t /= 10;
            }
            if (s % m == 0) cnt++;
        }
        return cnt;
    }

private:
    int n, m;
};

// ÊýÎ»dp
class Solution2
{
public:
    Solution2(int n, int m) : n(n), m(m) {}

    int solve()
    {
        digits = getDigits(n);
        cache = vector<vector<vector<int>>>(digits.size() + 1, vector<vector<int>>(m, vector<int>(2, -1)));
        return dp(0, 0, true);
    }

private:
    int n, m;
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

    int dp(int index, int sum, bool top)
    {
        if (cache[index][sum][top] != -1) return cache[index][sum][top];
        if (index == (int)digits.size()) return cache[index][sum][top] = (sum % m == 0) ? 1 : 0;
        int upper = top ? digits[index] : 9;
        int cnt = 0;
        for (int i = 0; i <= upper; ++i)
        {
            cnt += dp(index + 1, (sum + i) % m, top && i == digits[index]);
        }
        return cache[index][sum][top] = cnt;
    }
};

int main()
{
    int a, b, m;
    while (cin >> a >> b >> m)
    {
        //cout << Solution1(b, m).solve() - Solution1(a - 1, m).solve() << endl;
        cout << Solution2(b, m).solve() - Solution2(a - 1, m).solve() << endl;
    }

    return 0;
}