// https://www.luogu.com.cn/problem/P1048

#include <iostream>
#include <vector>

using namespace std;

struct Object
{
	int time;
	int value;
};

class Solver
{
public:
	int solve(const vector<Object>& objects, int totalTime)
	{
		this->objects = objects;

		cache = vector<vector<int>>(MAX_OBJECT_COUNT, vector<int>(MAX_TOTAL_TIME, -1));

		return dp(0, totalTime);
	}

private:
	const int MAX_TOTAL_TIME = 1005;
	const int MAX_OBJECT_COUNT = 105;

	vector<Object> objects;
	
	vector<vector<int>> cache;


	int dp(int currentObjectIndex, int leftTime)
	{
		if (leftTime < 0)
		{
			return 0;
		}

		if (currentObjectIndex >= (int)objects.size())
		{
			return 0;
		}

		if (cache[currentObjectIndex][leftTime] != -1)
		{
			return cache[currentObjectIndex][leftTime];
		}

		const Object& currentObject = objects[currentObjectIndex];
		int ret = dp(currentObjectIndex + 1, leftTime);
		if (leftTime >= currentObject.time)
		{
			ret = max(ret, currentObject.value + dp(currentObjectIndex + 1, leftTime - currentObject.time));
		}

		cache[currentObjectIndex][leftTime] = ret;
		return ret;
	}
};

int main()
{
	int totalTime, objectCount;
	cin >> totalTime >> objectCount;

	vector<Object> objects;
	for (int i = 0; i < objectCount; ++i)
	{
		Object object;
		cin >> object.time >> object.value;
		objects.push_back(object);
	}

	cout << Solver().solve(objects, totalTime);

	return 0;
}