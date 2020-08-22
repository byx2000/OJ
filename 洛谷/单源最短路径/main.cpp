// https://www.luogu.com.cn/problem/P3371
// https://www.luogu.com.cn/problem/P4779

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

#define INF (INT_MAX / 2)

struct Edge
{
	int to, distance;
	Edge(int to, int distance) : to(to), distance(distance) {}
};

// 解法1：分支限界法（普通队列）
class Solution1
{
public:
	Solution1(const vector<vector<Edge>>& edges, int start)
		: edges(edges), start(start) {}

	vector<int> solve()
	{
		int cNode = edges.size();

		vector<int> shortest(cNode, INF);

		queue<Node> q;
		q.push(Node(start, 0));

		while (!q.empty())
		{
			Node node = q.front();
			int iNode = node.iNode;
			int distance = node.distance;

			q.pop();

			if (distance >= shortest[iNode])
			{
				continue;
			}

			shortest[iNode] = distance;

			for (int i = 0; i < (int)edges[iNode].size(); ++i)
			{
				int to = edges[iNode][i].to;
				int dis = edges[iNode][i].distance;
				q.push(Node(to, distance + dis));
			}
		}

		return shortest;
	}

private:
	vector<vector<Edge>> edges;
	int start;

	struct Node
	{
		int iNode;
		int distance;
		Node(int iNode, int dis) : iNode(iNode), distance(dis) {}
		bool operator>(const Node& n) const { return distance > n.distance; }
	};
};

// 解法2：分支限界法（优先队列）
class Solution2
{
public:
	Solution2(const vector<vector<Edge>>& edges, int start)
		: edges(edges), start(start) {}

	vector<int> solve()
	{
		int cNode = edges.size();

		vector<int> shortest(cNode, INF);

		priority_queue<Node, vector<Node>, greater<Node>> pq;
		pq.push(Node(start, 0));

		while (!pq.empty())
		{
			Node node = pq.top();
			int iNode = node.iNode;
			int distance = node.distance;

			pq.pop();

			if (distance >= shortest[iNode])
			{
				continue;
			}

			shortest[iNode] = distance;

			for (int i = 0; i < (int)edges[iNode].size(); ++i)
			{
				int to = edges[iNode][i].to;
				int dis = edges[iNode][i].distance;
				pq.push(Node(to, distance + dis));
			}
		}

		return shortest;
	}

private:
	vector<vector<Edge>> edges;
	int start;

	struct Node
	{
		int iNode;
		int distance;
		Node(int iNode, int dis) : iNode(iNode), distance(dis) {}
		bool operator>(const Node& n) const { return distance > n.distance; }
	};
};

// 解法3：分支限界法（优先队列、标记已访问节点）
class Solution3
{
public:
	Solution3(const vector<vector<Edge>>& edges, int start)
		: edges(edges), start(start) {}

	vector<int> solve()
	{
		int cNode = edges.size();

		vector<int> shortest(cNode, INF);
		vector<bool> visited(cNode, false);

		priority_queue<Node, vector<Node>, greater<Node>> pq;
		pq.push(Node(start, 0));

		while (!pq.empty())
		{
			Node node = pq.top();
			int iNode = node.iNode;
			int distance = node.distance;

			pq.pop();

			if (visited[iNode])
			{
				continue;
			}
			visited[iNode] = true;

			shortest[iNode] = distance;

			for (int i = 0; i < (int)edges[iNode].size(); ++i)
			{
				int to = edges[iNode][i].to;
				int dis = edges[iNode][i].distance;
				pq.push(Node(to, distance + dis));
			}
		}

		return shortest;
	}

private:
	vector<vector<Edge>> edges;
	int start;

	struct Node
	{
		int iNode;
		int distance;
		Node(int iNode, int dis) : iNode(iNode), distance(dis) {}
		bool operator>(const Node& n) const { return distance > n.distance; }
	};
};

int main()
{
	int cNode, cEdge, start;
	cin >> cNode >> cEdge >> start;

	vector<vector<Edge>> edges(cNode);
	for (int i = 0; i < cEdge; ++i)
	{
		int from, to, distance;
		cin >> from >> to >> distance;
		edges[from - 1].push_back(Edge(to - 1, distance));
	}

	//vector<int> res = Solution1(edges, start - 1).solve();
	//vector<int> res = Solution2(edges, start - 1).solve();
	vector<int> res = Solution3(edges, start - 1).solve();

	for (int i = 0; i < cNode; ++i)
	{
		cout << (res[i] == INF ? INT_MAX : res[i]) << " ";
	}

	return 0;
}