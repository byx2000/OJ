/*
* LeetCode题解公共头文件
* 包含C++标准库常用头文件，以及单元测试工具
* 单元测试工具用于LeetCode题目样例的测试
*/

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <cassert>

using namespace std;

// 断言
class Assert
{
public:
    // 是否为真
    // 适用于所有能够转换成bool的类型
    template<typename T>
    static bool isTrue(const T& condition)
    {
        return condition;
    }

    // 是否相等
    // 适用于所有可以用==比较的类型
    template<typename T1, typename T2>
    static bool areEqual(const T1& a, const T2& b)
    {
        return a == b;
    }

    // 浮点数相等偏特化版本
    template<>
    static bool areEqual<double, double>(const double& a, const double& b)
    {
        return fabs(a - b) < 1e-6;
    }

    // 判断集合是否相等
    // 适用于C++容器类：vector、string等
    // 集合相等意味着两集合所含元素相等，不考虑元素顺序
    template<typename T>
    static bool areEquivalent(const T& a, const T& b)
    {
        if (size(a) != size(b))
        {
            return false;
        }
        return set<T::value_type>(begin(a), end(a)) == set<T::value_type>(begin(b), end(b));
    }

    // 判断集合是否相等
    // 适用于传统C风格数组
    // 集合相等意味着两集合所含元素相等，不考虑元素顺序
    template<typename T, int Size1, int Size2>
    static bool areEquivalent(T(&a)[Size1], T(&b)[Size2])
    {
        if (Size1 != Size2)
        {
            return false;
        }
        return set<T>(begin(a), end(a)) == set<T>(begin(b), end(b));
    }
};

// 单元测试
// 当条件condition为假时，程序退出，并打印出错行号
#define TEST(condition) do{if(!(condition))assert(false);}while(0)

// 二叉树节点
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 构建列表
template<typename T>
vector<T> BuildList(const initializer_list<T>& list)
{
    return vector<T>(list.begin(), list.end());
}

// 批量测试

// 测试用例数据类型
template<typename... Args>
using Cases = vector<tuple<Args...>>;

// 1个输入
template<typename C, typename T1, typename T2, typename T>
void test(T(C::* func)(T1), const Cases<T2, T>& cases)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T2 input1 = get<0>(cases[i]);
		T output = (C().*func)(input1);
		T expected = get<1>(cases[i]);
		if (output == expected)
		{
			cout << "Test case " << i + 1 << " passed!" << endl << endl;
		}
		else
		{
			failed = true;
			cout << "Test case " << i + 1 << " failed:" << endl;
			cout << "output: " << output << "\texpected: " << expected << endl;
			cout << endl;
		}
	}

	if (!failed)
	{
		cout << "All test cases passed!" << endl;
	}
}

// 2个输入
template<typename C, typename T1, typename T2, typename T3, typename T4, typename T>
void test(T(C::* func)(T1, T2), const Cases<T3, T4, T>& cases)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T3 input1 = get<0>(cases[i]);
		T4 input2 = get<1>(cases[i]);
		T output = (C().*func)(input1, input2);
		T expected = get<2>(cases[i]);
		if (output == expected)
		{
			cout << "Test case " << i + 1 << " passed!" << endl << endl;
		}
		else
		{
			failed = true;
			cout << "Test case " << i + 1 << " failed:" << endl;
			cout << "output: " << output << "\texpected: " << expected << endl;
			cout << endl;
		}
	}

	if (!failed)
	{
		cout << "All test cases passed!" << endl;
	}
}

// 3个输入
template<typename C, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T>
void test(T(C::* func)(T1, T2, T3), const Cases<T4, T5, T6, T>& cases)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T4 input1 = get<0>(cases[i]);
		T5 input2 = get<1>(cases[i]);
		T6 input3 = get<2>(cases[i]);
		T output = (C().*func)(input1, input2, input3);
		T expected = get<3>(cases[i]);
		if (output == expected)
		{
			cout << "Test case " << i + 1 << " passed!" << endl << endl;
		}
		else
		{
			failed = true;
			cout << "Test case " << i + 1 << " failed:" << endl;
			cout << "output: " << output << "\texpected: " << expected << endl;
			cout << endl;
		}
	}

	if (!failed)
	{
		cout << "All test cases passed!" << endl;
	}
}

// 重载vector<T>输出
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v)
{
	o << "[";
	for (int i = 0; i < (int)v.size(); ++i)
	{
		o << v[i];
		if (i != (int)v.size() - 1)
		{
			o << ",";
		}
		else
		{
			o << "]";
		}
	}
	return o;
}

#endif
