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

#endif
