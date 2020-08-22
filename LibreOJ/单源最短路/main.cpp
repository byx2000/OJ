// https://loj.ac/problem/119

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define INF (INT_MAX / 2)

struct Edge
{
	int to, distance;
	Edge(int to, int distance) : to(to), distance(distance) {}
};

// 解法1：分支限界法（记录出发节点到其余节点的当前最短路径）
class Solution1
{
public:
	Solution1(const vector<vector<Edge>>& edges, int iStart, int iEnd)
		: edges(edges), iStart(iStart), iEnd(iEnd) {}

	int solve()
	{
		int cNode = edges.size();

		priority_queue<State, vector<State>, greater<State>> pq;
		pq.push(State(iStart, 0));

		vector<int> shortest(cNode, INF);

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			int iNode = state.iNode;
			int distance = state.distance;

			if (iNode == iEnd)
			{
				return distance;
			}

			if (distance >= shortest[iNode])
			{
				continue;
			}

			shortest[iNode] = distance;

			for (int i = 0; i < (int)edges[iNode].size(); ++i)
			{
				int to = edges[iNode][i].to;
				int dis = edges[iNode][i].distance;
				pq.push(State(to, distance + dis));
			}
		}

		return 0;
	}

private:
	vector<vector<Edge>> edges;
	int iStart, iEnd;

	struct State
	{
		int iNode;
		int distance;
		State(int iNode, int distance) : iNode(iNode), distance(distance) {}
		bool operator>(const State& n) const { return distance > n.distance; }
	};
};

// 解法2：分支限界法（记录已扩展的节点，禁止重复扩展）
class Solution2
{
public:
	Solution2(const vector<vector<Edge>>& edges, int iStart, int iEnd)
		: edges(edges), iStart(iStart), iEnd(iEnd) {}

	int solve()
	{
		int cNode = edges.size();

		priority_queue<State, vector<State>, greater<State>> pq;
		pq.push(State(iStart, 0));

		vector<bool> book(cNode, false);

		while (!pq.empty())
		{
			State state = pq.top();
			pq.pop();
			int iNode = state.iNode;
			int distance = state.distance;

			if (iNode == iEnd)
			{
				return distance;
			}

			if (book[iNode])
			{
				continue;
			}

			book[iNode] = true;

			for (int i = 0; i < (int)edges[iNode].size(); ++i)
			{
				int to = edges[iNode][i].to;
				int dis = edges[iNode][i].distance;
				pq.push(State(to, distance + dis));
			}
		}

		return 0;
	}

private:
	vector<vector<Edge>> edges;
	int iStart, iEnd;

	struct State
	{
		int iNode;
		int distance;
		State(int iNode, int distance) : iNode(iNode), distance(distance) {}
		bool operator>(const State& n) const { return distance > n.distance; }
	};
};

int main()
{
	
	int cNode, cEdge, iStart, iEnd;
	cin >> cNode >> cEdge >> iStart >> iEnd;

	vector<vector<Edge>> edges(cNode);
	for (int i = 0; i < cEdge; ++i)
	{
		int u, v, d;
		cin >> u >> v >> d;
		edges[u - 1].push_back(Edge(v - 1, d));
		edges[v - 1].push_back(Edge(u - 1, d));
	}

	//cout << Solution1(edges, iStart - 1, iEnd - 1).solve();
	cout << Solution2(edges, iStart - 1, iEnd - 1).solve();

	return 0;
}