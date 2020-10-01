// https://www.luogu.com.cn/problem/P1896

#include <iostream>
#include <vector>

using namespace std;

// »ØËÝ·¨
class Solution1
{
public:
    Solution1(int n, int k) : n(n), k(k)
    {
        board = vector<int>(n * n, 0);
        offset = vector<vector<int>>
        {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {1, -1},
            {1, 0},
            {1, 1},
            {0, -1},
            {0, 1},
        };
    }

    int solve()
    {
        cnt = 0;
        dfs(0, 0);
        return cnt;
    }

private:
    int n, k;
    vector<int> board;
    int cnt;
    vector<vector<int>> offset;

    bool valid(int i)
    {
        return i >= 0 && i < n;
    }

    void set(int pos)
    {
        board[pos]++;
        int r = pos / n;
        int c = pos % n;
        for (int i = 0; i < (int)offset.size(); ++i)
        {
            int nr = r + offset[i][0];
            int nc = c + offset[i][1];
            if (valid(nr) && valid(nc)) board[nr * n + nc]++;
        }
    }

    void unset(int pos)
    {
        board[pos]--;
        int r = pos / n;
        int c = pos % n;
        for (int i = 0; i < (int)offset.size(); ++i)
        {
            int nr = r + offset[i][0];
            int nc = c + offset[i][1];
            if (valid(nr) && valid(nc)) board[nr * n + nc]--;
        }
    }

    bool canSet(int pos)
    {
        return board[pos] == 0;
    }

    void dfs(int m, int last_pos)
    {
        if (m == k) { cnt++; return; }
        for (int next_pos = last_pos; next_pos < n * n; ++next_pos)
        {
            if (canSet(next_pos))
            {
                set(next_pos);
                dfs(m + 1, next_pos);
                unset(next_pos);
            }
        }
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    cout << Solution1(n, k).solve() << endl;

    return 0;
}