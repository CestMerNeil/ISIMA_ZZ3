#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

struct Node
{
    int x, y;
    double g_cost = 0.0;
    double h_cost = 0.0;
    int parent_x = -1;
    int parent_y = -1;

    double f_cost() const
    {
        return g_cost + h_cost;
    }

    bool operator>(const Node &other) const
    {
        return f_cost() > other.f_cost();
    }
};

class AStar
{
public:
    std::vector<Node> findPath(const std::vector<std::vector<int>> &grid, Node start, Node goal);

private:
    bool isValid(int x, int y, const std::vector<std::vector<int>> &grid) const;
    double calculateHeuristic(int x1, int y1, int x2, int y2) const;
};