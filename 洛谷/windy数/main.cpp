// https://www.luogu.com.cn/problem/P2657

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 暴力
class Solution1
{
public:
    Solution1(int n) : n(n) {}

    int solve()
    {
        int cnt = 0;
        for (int i = 0; i <= n; ++i)
        {
            int t = i;
            bool ret = true;
            int d = t % 10;
            t /= 10;
            while (t)
            {
                ret = ret && abs(t % 10 - d) >= 2;
                d = t % 10;
                t /= 10;
            }
            if (ret) cnt++;
        }
        return cnt;
    }

private:
    int n;
};

// 数位dp
class Solution2
{
public:
    Solution2(int n) : n(n) {}

    int solve()
    {
        if (n == 0) return 1;
        digits = getDigits(n);

        cache = vector<vector<vector<vector<int>>>>(digits.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(2, -1))));

        int cnt = 0;
        for (int i = 0; i <= digits[0]; ++i)
        {
            cnt += dfs(0, i, i == digits[0], i == 0);
        }

        return cnt;
    }

private:
    int n;
    vector<int> digits;
    vector<vector<vector<vector<int>>>> cache;

    // 将整数n的各个数位拆分出来
    vector<int> getDigits(int n)
    {
        vector<int> digits;
        while (n)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }

    // 第index位数字为d
    // top表示之前的数位是否到达最大值
    // zero表示之前的数位是否全是前导0
    int dfs(int index, int d, bool top, bool zero)
    {
        if (cache[index][d][top][zero] != -1) return cache[index][d][top][zero];

        if (index == (int)digits.size() - 1) return cache[index][d][top][zero] = 1;

        int upper = top ? digits[index + 1] : 9;
        int cnt = 0;
        for (int i = 0; i <= upper; ++i)
        {
            if (abs(i - d) >= 2 || zero)
            {
                cnt += dfs(index + 1, i, top && i == digits[index + 1], zero && i == 0);
            }
        }

        return cache[index][d][top][zero] = cnt;
    }
};

int main()
{

    int a, b;
    cin >> a >> b;
    //cout << Solution1(b).solve() - Solution1(a - 1).solve();
    cout << Solution2(b).solve() - Solution2(a - 1).solve();

    return 0;
}
