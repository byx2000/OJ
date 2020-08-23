// http://poj.org/problem?id=1129

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<vector<bool>>& adj) : adj(adj) {}

	int solve()
	{
		int cNode = adj.size();
		color = vector<int>(cNode, -1);

		return 0;
	}

private:
	vector<vector<bool>> adj;
	vector<int> color;

	void dfs(int index)
	{

	}
};

int main()
{
	cout << 123 << endl;
	return 0;
}