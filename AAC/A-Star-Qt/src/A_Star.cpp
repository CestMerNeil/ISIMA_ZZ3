#include "A_Star.hpp"
#include <limits>

std::vector<Node> AStar::findPath(const std::vector<std::vector<int>> &grid, Node start, Node goal)
{
    if (grid.empty() || grid[0].empty())
        return {};

    const int rows = grid.size();
    const int cols = grid[0].size();
    std::vector<std::vector<double>> g_score(rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));
    std::vector<std::vector<std::pair<int, int>>> came_from(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;

    start.g_cost = 0.0;
    start.h_cost = calculateHeuristic(start.x, start.y, goal.x, goal.y);
    g_score[start.x][start.y] = 0.0;
    openList.push(start);

    while (!openList.empty())
    {
        Node current = openList.top();
        openList.pop();

        if (current.x == goal.x && current.y == goal.y)
        {
            std::vector<Node> path;
            Node cur = current;
            while (cur.x != start.x || cur.y != start.y)
            {
                path.push_back(cur);
                int px = came_from[cur.x][cur.y].first;
                int py = came_from[cur.x][cur.y].second;
                cur.x = px;
                cur.y = py;
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (current.g_cost > g_score[current.x][current.y])
            continue;

        std::vector<std::pair<int, int>> neighbors = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto [dx, dy] : neighbors)
        {
            int newX = current.x + dx;
            int newY = current.y + dy;

            if (!isValid(newX, newY, grid))
                continue;

            double tentative_g = current.g_cost + 1.0;
            if (tentative_g < g_score[newX][newY])
            {
                came_from[newX][newY] = {current.x, current.y};
                g_score[newX][newY] = tentative_g;
                Node neighbor;
                neighbor.x = newX;
                neighbor.y = newY;
                neighbor.g_cost = tentative_g;
                neighbor.h_cost = calculateHeuristic(newX, newY, goal.x, goal.y);
                openList.push(neighbor);
            }
        }
    }

    return {};
}

bool AStar::isValid(int x, int y, const std::vector<std::vector<int>> &grid) const
{
    return x >= 0 && y >= 0 &&
           x < static_cast<int>(grid.size()) &&
           y < static_cast<int>(grid[0].size()) &&
           grid[x][y] == 0;
}

double AStar::calculateHeuristic(int x1, int y1, int x2, int y2) const
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}