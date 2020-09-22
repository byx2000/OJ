#include "common.h"

// ������
class Solver
{
public:
	double solve1(int n)
	{
		return n / 2.0;
	}

	int solve2(vector<int>& nums, int k)
	{
		return 0;
	}

	int solve3(vector<int>& v, string s, int b)
	{
		return v[0] + s.size() + b;
	}
};

int main()
{
	TEST(Assert::isTrue(true));
	TEST(!Assert::isTrue(false));

	TEST(Assert::areEqual(-3, -3));
	TEST(!Assert::areEqual(-3, 2));
	TEST(Assert::areEqual(3.14, 3.14));
	TEST(!Assert::areEqual(3.14, 1.57));
	TEST(Assert::areEqual(vector<int>{1, 2, 3}, vector<int>{1, 2, 3}));
	TEST(!Assert::areEqual(vector<int>{1, 2, 3}, vector<int>{1, 2, 3, 4}));
	TEST(!Assert::areEqual(vector<int>{1, 2, 3}, vector<int>{3, 2, 1}));
	TEST(Assert::areEqual(string("abc"), "abc"));
	TEST(!Assert::areEqual("123", string("1234")));

	TEST(Assert::areEquivalent(vector<int>{3, 1, 4, 2}, vector<int>{1, 2, 3, 4}));
	TEST(!Assert::areEquivalent(vector<int>{3, 1, 4, 2}, vector<int>{2, 1, 4, 5}));
	TEST(!Assert::areEquivalent(vector<int>{3, 3, 3}, vector<int>{3, 3}));
	{
		int a[] = { 1, 2, 3, 4, 5 };
		int b[] = { 5, 4, 3, 1, 2 };
		TEST(Assert::areEquivalent(a, b));
	}
	{
		int a[] = { 3, 3, 3 };
		int b[] = { 3, 3 };
		TEST(!Assert::areEquivalent(a, b));
	}

	TEST(Assert::areEqual(BuildList({ 1, 2, 3, 4, 5 }), vector<int>{1, 2, 3, 4, 5}));
	TEST(Assert::areEqual(BuildList<int>({}), vector<int>{}));

	Cases<vector<int>, string, int, int> cases1
	{
		{ {2, 3}, "abc", 3, 8},
		{ {4}, "ab", 7, 13},
	};

	test(&Solver::solve3, cases1);
	cout << endl;

	Cases<int, double> cases2
	{
		{ 3, 1.5 },
		{ 6, 3.01 },
	};

	test(&Solver::solve1, cases2);
	cout << endl;

	Cases<vector<int>, int, int> cases3
	{
		{{1, 2, 3}, 4, 5},
		{{4, 5}, 2, 7},
		{{5, 4, 3, 2}, 7, 10},
	};

	test(&Solver::solve2, cases3);

	vector<int> vi{ 1, 2, 3 };
	cout << vi << endl;

	vector<string> vs{ "abc", "de", "ghij" };
	cout << vs << endl;

	return 0;
}