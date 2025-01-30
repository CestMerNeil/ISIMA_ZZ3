#include "Grid.hpp"

void Grid::displayGrid(const std::vector<std::vector<int>> &grid, const std::vector<Node> &path)
{
    if (grid.empty())
    {
        std::cout << "Grid is empty.\n";
        return;
    }

    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<char>> displayGrid(rows, std::vector<char>(cols, '0'));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == 1)
                displayGrid[i][j] = 'X';
        }
    }

    for (const auto &node : path)
    {
        if (node.x >= 0 && node.x < rows && node.y >= 0 && node.y < cols)
            displayGrid[node.x][node.y] = '*';
    }

    for (const auto &row : displayGrid)
    {
        for (char cell : row)
            std::cout << cell << ' ';
        std::cout << '\n';
    }
}