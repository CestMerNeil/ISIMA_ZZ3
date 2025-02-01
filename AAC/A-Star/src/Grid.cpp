#include "Grid.hpp"

/**
 * @brief Constructeur de la grille avec initialisation de la matrice.
 */
Grid::Grid(int rows, int cols)
    : grid(rows, std::vector<int>(cols, 0))
{
}

/**
 * @brief Ajoute un obstacle à la position (x, y).
 */
void Grid::ajouterObstacle(int x, int y)
{
    if (x >= 0 && x < static_cast<int>(grid.size()) &&
        y >= 0 && y < static_cast<int>(grid[0].size()))
    {
        grid[x][y] = 1; // 1 représente un obstacle
    }
}

/**
 * @brief Retourne une référence constante vers la grille interne.
 */
const std::vector<std::vector<int>> &Grid::getGrid() const
{
    return grid;
}

/**
 * @brief Affiche la grille et le chemin (si fourni) dans la console.
 */
void Grid::displayGrid(const std::vector<std::vector<int>> &grid, const std::vector<Node> &path)
{
    if (grid.empty())
    {
        std::cout << "La grille est vide.\n";
        return;
    }

    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());

    // Construction d'une grille d'affichage basée sur des caractères
    std::vector<std::vector<char>> displayGrid(rows, std::vector<char>(cols, '0'));

    // Marquer les obstacles
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (grid[i][j] == 1)
            {
                displayGrid[i][j] = 'X'; // 'X' pour un obstacle
            }
        }
    }

    // Marquer le chemin
    for (const auto &node : path)
    {
        if (node.x >= 0 && node.x < rows && node.y >= 0 && node.y < cols)
        {
            displayGrid[node.x][node.y] = '*'; // '*' représente le chemin
        }
    }

    // Affichage final
    for (const auto &row : displayGrid)
    {
        for (char cell : row)
        {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}