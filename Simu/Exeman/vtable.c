// 虚函数调用的机制
#include <stdio.h>

// 基类定义虚函数
typedef struct Base
{
    void (*virtualFunction)();
} Base;

// 派生类定义虚函数
void DerivedFunction()
{
    printf("DerivedFunction\n");
}

int main()
{
    Base base;
    Base derived;
    base.virtualFunction = NULL;
    derived.virtualFunction = DerivedFunction;
    derived.virtualFunction();
    return 0;
}