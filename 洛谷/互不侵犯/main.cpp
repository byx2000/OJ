// https://www.luogu.com.cn/problem/P1896

#include <iostream>
#include <vector>

using namespace std;

// ���ݷ�
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

    // ��ǰ���ڷŵ�m���������ϸ���������λ��Ϊlast_pos
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

// ״̬ѹ��dp
class Solution2
{
public:
    Solution2(int n, int k) : n(n), k(k) {}

    long long solve()
    {
        cache = vector<vector<vector<long long>>>(n + 1, vector<vector<long long>>(1 << n, vector<long long>(n * n + 1, -1)));
        return dp(0, 0, 0);
    }

private:
    int n, k;
    vector<vector<vector<long long>>> cache;

    // �ж���״̬�Ƿ�Ϸ����Ƿ����������ڵĹ�����
    bool valid(int s)
    {
        return !(s & (s << 1));
    }

    // �ж����������Ƿ�Ϸ�
    bool valid(int s1, int s2)
    {
        return !(s1 & s2) && !(s1 & (s2 << 1)) && !(s2 & (s1 << 1));
    }

    // �жϵ�ǰ���ж��ٸ�����
    int count(int s)
    {
        if (s == 0) return 0;
        return s % 2 + count(s >> 1);
    }

    // ��ǰ���ڵ�r�У���һ�е�״̬Ϊs��Ŀǰ�Ѿ�����c������
    long long dp(int r, int s, int c)
    {
        if (cache[r][s][c] != -1) return cache[r][s][c];
        if (r == n) return cache[r][s][c] = (c == k) ? 1 : 0;

        long long cnt = 0;
        for (int i = 0; i < (1 << n); ++i)
        {
            if (valid(i) && valid(s, i))
            {
                cnt += dp(r + 1, i, c + count(i));
            }
        }
        return cache[r][s][c] = cnt;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    //cout << Solution1(n, k).solve() << endl;
    cout << Solution2(n, k).solve() << endl;

    return 0;
}