/*
* LeetCode��⹫��ͷ�ļ�
* ����C++��׼�ⳣ��ͷ�ļ����Լ���Ԫ���Թ���
* ��Ԫ���Թ�������LeetCode��Ŀ�����Ĳ���
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

// ����
class Assert
{
public:
    // �Ƿ�Ϊ��
    // �����������ܹ�ת����bool������
    template<typename T>
    static bool isTrue(const T& condition)
    {
        return condition;
    }

    // �Ƿ����
    // ���������п�����==�Ƚϵ�����
    template<typename T1, typename T2>
    static bool areEqual(const T1& a, const T2& b)
    {
        return a == b;
    }

    // ���������ƫ�ػ��汾
    template<>
    static bool areEqual<double, double>(const double& a, const double& b)
    {
        return fabs(a - b) < 1e-6;
    }

    // �жϼ����Ƿ����
    // ������C++�����ࣺvector��string��
    // ���������ζ������������Ԫ����ȣ�������Ԫ��˳��
    template<typename T>
    static bool areEquivalent(const T& a, const T& b)
    {
        if (size(a) != size(b))
        {
            return false;
        }
        return set<T::value_type>(begin(a), end(a)) == set<T::value_type>(begin(b), end(b));
    }

    // �жϼ����Ƿ����
    // �����ڴ�ͳC�������
    // ���������ζ������������Ԫ����ȣ�������Ԫ��˳��
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

// ��Ԫ����
// ������conditionΪ��ʱ�������˳�������ӡ�����к�
#define TEST(condition) do{if(!(condition))assert(false);}while(0)

// �������ڵ�
struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// �����б�
template<typename T>
vector<T> BuildList(const initializer_list<T>& list)
{
    return vector<T>(list.begin(), list.end());
}

// ��������

// ����������������
template<typename... Args>
using Cases = vector<tuple<Args...>>;

// 1������
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

// 2������
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

// 3������
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

// ����vector<T>���
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
