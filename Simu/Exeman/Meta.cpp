// 元编程是利用 C++ 模板系统在编译期生成代码，常用于优化和提高代码的可复用性。
#include <iostream>
using namespace std;

// 计算阶乘的编译期元编程
template <int N>
struct Factorial
{
    static const int value = N * Factorial<N - 1>::value;
};

// 阶乘的终止条件
template <>
struct Factorial<0>
{
    static const int value = 1;
};

int main()
{
    cout << Factorial<5>::value << endl;
    return 0;
}