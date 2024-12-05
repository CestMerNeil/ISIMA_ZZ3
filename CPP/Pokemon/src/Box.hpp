#pragma once
#include <utility>

template <typename T>
class Box
{
private:
    T value;

public:
    explicit Box(const T &value) : value(value) {}
    explicit Box(T &&value) : value(std::move(value)) {}

    inline T getValue() const { return value; }
};