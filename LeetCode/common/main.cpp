#include "common.h"

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

	return 0;
}