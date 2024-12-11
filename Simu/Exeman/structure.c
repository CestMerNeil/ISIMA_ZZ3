// 动态继承的结构设计
#include <stdio.h>
#include <stdlib.h>

// 定义类结构
typedef struct Class
{
    const char *name;
    struct Class *parent;
} Class;

// 动态插入类
void insertClass(Class *class, Class *parent)
{
    class->parent = parent;
}

int main()
{
    Class base = {"Base", NULL};
    Class derived = {"Derived", NULL};

    insertClass(&derived, &base);
    return 0;
}