// https://www.luogu.com.cn/problem/P1803

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Line
{
	int start;
	int end;
};

// Ì°ĞÄËã·¨
class Solution
{
public:
	Solution(const vector<Line>& lines) : lines(lines) {}

	int solve()
	{
		// °´ÕÕÏß¶ÎÄ©¶Ë×ø±êÅÅĞò
		sort(lines.begin(), lines.end(), 
			[](const Line& a, const Line& b) 
			{ 
				return a.end < b.end; 
			});

		int count = 0;
		int lastEnd = 0;
		for (int i = 0; i < (int)lines.size(); ++i)
		{
			if (lines[i].start >= lastEnd)
			{
				count++;
				lastEnd = lines[i].end;
			}
		}

		return count;
	}

private:
	vector<Line> lines;
};

int main()
{
	int n;
	cin >> n;

	vector<Line> lines(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> lines[i].start >> lines[i].end;
	}

	cout << Solution(lines).solve();

	return 0;
}