
#ifndef CHAINE_HPP
#define CHAINE_HPP

#include <iostream>
#include <string>
#include "exception.hpp"
#include "demangle.hpp"
#include <tuple>

template <typename T>
std::string chaine(const T &x)
{

    throw ExceptionChaine("Conversion en chaine impossible pour '" + demangle(typeid(x).name()) + "'");
}

template <>
std::string chaine(const int &x)
{
    return std::to_string(x);
}

template <>
std::string chaine(const double &x)
{
    return std::to_string(x);
}

template <>
std::string chaine(const std::string &x)
{
    return x;
}

template <>
std::string chaine(const std::tuple<int, int, int> &x)
{
    int x1 = std::get<0>(x);
    int x2 = std::get<1>(x);
    int x3 = std::get<2>(x);
    return std::to_string(x1) + " " + std::to_string(x2) + " " + std::to_string(x3);
}

template <typename T1, typename T2>
std::string chaine(const std::tuple<T1, T2> &x)
{
    T1 x1 = std::get<0>(x);
    T2 x2 = std::get<1>(x);
    return chaine(x1) + " " + chaine(x2);
}

template <typename T1, typename T2, typename T3>
std::string chaine(const T1 x, const T2 y, const T3 z)
{
    return chaine(x) + " " + chaine(y) + " " + chaine(z);
}

template <typename T1, typename T2, typename T3>
std::string chaine(const std::tuple<T1, T2, T3> &x)
{
    T1 x1 = std::get<0>(x);
    T2 x2 = std::get<1>(x);
    T3 x3 = std::get<2>(x);
    return chaine(x1) + " " + chaine(x2) + " " + chaine(x3);
}

template <typename T1, typename T2, typename T3, typename T4>
std::string chaine(const T1 x, const T2 y, const T3 z, const T4 w)
{
    return chaine(x) + " " + chaine(y) + " " + chaine(z) + " " + chaine(w);
}

template <typename T1, typename T2, typename T3, typename T4>
std::string chaine(const std::tuple<T1, T2, T3, T4> &x)
{
    T1 x1 = std::get<0>(x);
    T2 x2 = std::get<1>(x);
    T3 x3 = std::get<2>(x);
    T4 x4 = std::get<3>(x);
    return chaine(x1) + " " + chaine(x2) + " " + chaine(x3) + " " + chaine(x4);
}

#endif // CHAINE_HPP

/*

// Code refactoring given by ChatGPT. But it is not working properly.

#ifndef CHAINE_HPP
#define CHAINE_HPP

#include <iostream>
#include <string>
#include <tuple>
#include "exception.hpp"
#include "demangle.hpp"

// 通用模板转换函数：抛出自定义异常
template <typename T>
std::string convert(const T &x)
{
    throw ExceptionChaine("Conversion en chaine impossible pour '" + demangle(typeid(x).name()) + "'");
}

// 对于特定类型的模板特化
template <>
std::string convert(const int &x)
{
    return std::to_string(x);
}

template <>
std::string convert(const double &x)
{
    return std::to_string(x);
}

template <>
std::string convert(const std::string &x)
{
    return x;
}

// 递归解包元组的辅助函数
template <typename Tuple, std::size_t... I>
std::string tuple_to_string_impl(const Tuple &t, std::index_sequence<I...>)
{
    return ((convert(std::get<I>(t)) + " ") + ...); // 使用 fold expression 展开元组并添加空格
}

// 元组类型的转换函数
template <typename... Args>
std::string convert(const std::tuple<Args...> &t)
{
    return tuple_to_string_impl(t, std::index_sequence_for<Args...>{});
}

// 任意数量参数的通用字符串转换函数
template <typename... Args>
std::string chaine(const Args &...args)
{
    return (convert(args) + ...); // 使用 fold expression 展开参数包
}

#endif // CHAINE_HPP
*/