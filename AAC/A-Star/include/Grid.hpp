#pragma once
#include <vector>
#include <iostream>
#include "A_Star.hpp"

class Grid
{
public:
    void displayGrid(const std::vector<std::vector<int>> &grid, const std::vector<Node> &path);
};