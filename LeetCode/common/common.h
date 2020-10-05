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
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 一个不会出现在二叉树中的值，表示空节点
const int null = numeric_limits<int>::max();

// 解析LeetCode二叉树格式，创建二叉树
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

// 判断二叉树是否相等
bool TreeEqual(TreeNode* t1, TreeNode* t2)
{
	if (t1 == NULL && t2 != NULL) return false;
	if (t1 != NULL && t2 == NULL) return false;
	if (t1 == NULL && t2 == NULL) return true;
	return t1->val == t2->val && TreeEqual(t1->left, t2->left) && TreeEqual(t1->right, t2->right);
}

// 释放二叉树
void DestroyTree(TreeNode* root)
{
	if (root == NULL) return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	delete(root);
}

// 重载vector<T>输出
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

// 批量测试

// 判断相等
template<typename T>
bool equal(T a, T b)
{
	return a == b;
}

// 判断等价
template<typename T>
bool equivalent(T a, T b)
{
	return set<T::value_type>(begin(a), end(a)) == set<T::value_type>(begin(b), end(b));
}

// 测试用例数据类型
template<typename... Args>
using Cases = vector<tuple<Args...>>;

// 1个输入
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

// 2个输入
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

// 3个输入
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
