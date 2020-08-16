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

	bool cacheExist(int currentObjectIndex, int leftTime)
	{
		return cache[currentObjectIndex][leftTime] != -1;
	}

	int getCache(int currentObjectIndex, int leftTime)
	{
		return cache[currentObjectIndex][leftTime];
	}

	void setCache(int currentObjectIndex, int leftTime, int value)
	{
		cache[currentObjectIndex][leftTime] = value;
	}

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

		if (cacheExist(currentObjectIndex, leftTime))
		{
			return getCache(currentObjectIndex, leftTime);
		}

		const Object& currentObject = objects[currentObjectIndex];
		int ret = dp(currentObjectIndex + 1, leftTime);
		if (leftTime >= currentObject.time)
		{
			ret = max(ret, currentObject.value + dp(currentObjectIndex + 1, leftTime - currentObject.time));
		}

		setCache(currentObjectIndex, leftTime, ret);
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