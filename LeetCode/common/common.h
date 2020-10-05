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
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// һ����������ڶ������е�ֵ����ʾ�սڵ�
const int null = numeric_limits<int>::max();

// ����LeetCode��������ʽ������������
TreeNode* BuildTree(const vector<int>& nums)
{
	queue<TreeNode*> q;
	TreeNode* root = new TreeNode(nums[0]);
	q.push(root);
	for (int i = 1; i < (int)nums.size(); i += 2)
	{
		if (q.empty()) break;
		TreeNode* cur = q.front();
		q.pop();
		cur->left = (nums[i] != null) ? new TreeNode(nums[i]) : NULL;
		cur->right = (i + 1 < (int)nums.size() && nums[i + 1] != null) ? new TreeNode(nums[i + 1]) : NULL;
		if (cur->left != NULL) q.push(cur->left);
		if (cur->right != NULL) q.push(cur->right);
	}
	return root;
}

// �ж϶������Ƿ����
bool TreeEqual(TreeNode* t1, TreeNode* t2)
{
	if (t1 == NULL && t2 != NULL) return false;
	if (t1 != NULL && t2 == NULL) return false;
	if (t1 == NULL && t2 == NULL) return true;
	return t1->val == t2->val && TreeEqual(t1->left, t2->left) && TreeEqual(t1->right, t2->right);
}

// �ͷŶ�����
void DestroyTree(TreeNode* root)
{
	if (root == NULL) return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	delete(root);
}

// ����vector<T>���
template<typename T>
ostream& operator<<(ostream& o, const vector<T, allocator<T>>& v)
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

// ��������

// �ж����
template<typename T>
bool equal(T a, T b)
{
	return a == b;
}

// �жϵȼ�
template<typename T>
bool equivalent(T a, T b)
{
	return set<T::value_type>(begin(a), end(a)) == set<T::value_type>(begin(b), end(b));
}

// ����������������
template<typename... Args>
using Cases = vector<tuple<Args...>>;

// 1������
template<typename C, typename T1, typename T2, typename T>
void test(T(C::* func)(T1), const Cases<T2, T>& cases, bool(*cmp)(T, T) = equal<T>)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T2 input1 = get<0>(cases[i]);
		T output = (C().*func)(input1);
		T expected = get<1>(cases[i]);
		if (cmp(output, expected))
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
void test(T(C::* func)(T1, T2), const Cases<T3, T4, T>& cases, bool(*cmp)(T, T) = equal<T>)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T3 input1 = get<0>(cases[i]);
		T4 input2 = get<1>(cases[i]);
		T output = (C().*func)(input1, input2);
		T expected = get<2>(cases[i]);
		if (cmp(output, expected))
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
void test(T(C::* func)(T1, T2, T3), const Cases<T4, T5, T6, T>& cases, bool(*cmp)(T, T) = equal<T>)
{
	bool failed = false;
	for (size_t i = 0; i < cases.size(); ++i)
	{
		T4 input1 = get<0>(cases[i]);
		T5 input2 = get<1>(cases[i]);
		T6 input3 = get<2>(cases[i]);
		T output = (C().*func)(input1, input2, input3);
		T expected = get<3>(cases[i]);
		if (cmp(output, expected))
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

#endif
