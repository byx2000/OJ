// https://www.luogu.com.cn/problem/P2051

#include <iostream>
#include <vector>

using namespace std;

// 回溯法
class Solution1
{
public:
    Solution1(int row, int col) : row(row), col(col), cnt(0) {}

    int solve()
    {
        rowCount = vector<int>(row, 0);
        colCount = vector<int>(col, 0);
        cnt = 0;
        dfs(0);
        return cnt;
    }

private:
    int row, col;
    vector<int> rowCount, colCount;
    int cnt;
    static const int MOD = 9999973;

    bool canSet(int pos)
    {
        int r = pos / col;
        int c = pos % col;
        return rowCount[r] < 2 && colCount[c] < 2;
    }

    void set(int pos)
    {
        int r = pos / col;
        int c = pos % col;
        rowCount[r]++;
        colCount[c]++;
    }

    void unset(int pos)
    {
        int r = pos / col;
        int c = pos % col;
        rowCount[r]--;
        colCount[c]--;
    }

    void dfs(int pos)
    {
        if (pos == row * col) { cnt = (cnt + 1) % MOD; return; }
        dfs(pos + 1);
        if (canSet(pos))
        {
            set(pos);
            dfs(pos + 1);
            unset(pos);
        }
    }
};

// 动态规划
class Solution2
{
public:
    Solution2(int row, int col) : row(row), col(col) {}

    long long solve()
    {
        cache = vector<vector<vector<long long>>>(row + 1, vector<vector<long long>>(col + 1, vector<long long>(col + 1, -1)));
        return dp(0, 0, 0);
    }

private:
    int row, col;
    static const int MOD = 9999973;
    vector<vector<vector<long long>>> cache;

    // 当前处于第r行，有c1列有一个棋子，有c2列有两个棋子（有(col-c1-c2)列没有棋子）
    long long dp(int r, int c1, int c2)
    {
        if (cache[r][c1][c2] != -1) return cache[r][c1][c2];

        // 所有行都放置完毕
        if (r == row) return cache[r][c1][c2] = 1;

        // 第r行不放棋子
        long long cnt = dp(r + 1, c1, c2);

        // 第r行放一个棋子
        if (c1 >= 1) // 将棋子放在有一个棋子的列上
            cnt = (cnt + (dp(r + 1, c1 - 1, c2 + 1) * c1) % MOD) % MOD; 
        if (col - c1 - c2 >= 1) // 将棋子放在没有棋子的列上
            cnt = (cnt + (dp(r + 1, c1 + 1, c2) * (col - c1 - c2)) % MOD) % MOD; 

        // 第r行放两个棋子
        if (c1 >= 2) // 两个都放在只有一个棋子的列
            cnt = (cnt + (dp(r + 1, c1 - 2, c2 + 2) * (c1 * (c1 - 1) / 2)) % MOD) % MOD; 
        if (col - c1 - c2 >= 2) // 两个都放在没有棋子的列
            cnt = (cnt + (dp(r + 1, c1 + 2, c2) * ((col - c1 - c2) * (col - c1 - c2 - 1) / 2)) % MOD) % MOD; 
        if (c1 >= 1 && col - c1 - c2 >= 1) // 一个放在只有一个棋子的列，一个放在没有棋子的列
            cnt = (cnt + (dp(r + 1, c1, c2 + 1) * c1 * (col - c1 - c2)) % MOD) % MOD;

        return cache[r][c1][c2] = cnt % MOD;
    }
};

int main()
{
    int row, col;
    cin >> row >> col;

    //cout << Solution1(row, col).solve();
    cout << Solution2(row, col).solve();

    return 0;
}