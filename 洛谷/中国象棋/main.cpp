// https://www.luogu.com.cn/problem/P2051

#include <iostream>
#include <vector>

using namespace std;

// ���ݷ�
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

// ��̬�滮
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

    // ��ǰ���ڵ�r�У���c1����һ�����ӣ���c2�����������ӣ���(col-c1-c2)��û�����ӣ�
    long long dp(int r, int c1, int c2)
    {
        if (cache[r][c1][c2] != -1) return cache[r][c1][c2];

        // �����ж��������
        if (r == row) return cache[r][c1][c2] = 1;

        // ��r�в�������
        long long cnt = dp(r + 1, c1, c2);

        // ��r�з�һ������
        if (c1 >= 1) // �����ӷ�����һ�����ӵ�����
            cnt = (cnt + (dp(r + 1, c1 - 1, c2 + 1) * c1) % MOD) % MOD; 
        if (col - c1 - c2 >= 1) // �����ӷ���û�����ӵ�����
            cnt = (cnt + (dp(r + 1, c1 + 1, c2) * (col - c1 - c2)) % MOD) % MOD; 

        // ��r�з���������
        if (c1 >= 2) // ����������ֻ��һ�����ӵ���
            cnt = (cnt + (dp(r + 1, c1 - 2, c2 + 2) * (c1 * (c1 - 1) / 2)) % MOD) % MOD; 
        if (col - c1 - c2 >= 2) // ����������û�����ӵ���
            cnt = (cnt + (dp(r + 1, c1 + 2, c2) * ((col - c1 - c2) * (col - c1 - c2 - 1) / 2)) % MOD) % MOD; 
        if (c1 >= 1 && col - c1 - c2 >= 1) // һ������ֻ��һ�����ӵ��У�һ������û�����ӵ���
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