/*
* LeetCode题解公共头文件
* 包含C++标准库常用头文件，以及单元测试工具
* 单元测试工具用于LeetCode题目样例的测试
*/

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <algorithm>
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
        return set<T>(begin(a), end(a)) == set<T>(begin(b), end(b));
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

#endif
