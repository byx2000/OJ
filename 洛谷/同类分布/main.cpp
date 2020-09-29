// https://www.luogu.com.cn/problem/P4127

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

long long cache[20][200][200][2];

// ÊýÎ»dp
class Solution1
{
public:
    Solution1(long long n) : n(n) {}

    long long solve()
    {
        digits = getDigits(n);
        long long cnt = 0;
        for (mod = 1; mod <= 9 * (int)digits.size(); ++mod)
        {
            memset(cache, -1, sizeof(cache));
            cnt += dp(0, 0, 0, true);
        }
        return cnt;
    }

private:
    long long n;
    vector<long long> digits;
    int mod;

    vector<long long> getDigits(long long n)
    {
        vector<long long> v;
        while (n)
        {
            v.push_back(n % 10);
            n /= 10;
        }
        reverse(v.begin(), v.end());
        return v;
    }

    long long dp(int index, int sum, int num, bool top)
    {
        if (cache[index][sum][num][top] != -1)
            return cache[index][sum][num][top];
        if (index == (int)digits.size())
            return cache[index][sum][num][top] = (mod == sum && num % mod == 0) ? 1 : 0;
        int upper = top ? digits[index] : 9;
        long long cnt = 0;
        for (int i = 0; i <= upper; ++i)
            cnt += dp(index + 1, sum + i, (num * 10 + i) % mod, top && i == digits[index]);
        return cache[index][sum][num][top] = cnt;
    }
};

int main()
{
    long long a, b;
    cin >> a >> b;
    cout << Solution1(b).solve() - Solution1(a - 1).solve();

    return 0;
}