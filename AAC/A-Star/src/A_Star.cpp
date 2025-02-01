#include "A_Star.hpp"
#include <limits>
#include <algorithm>
#include <queue>

/**
 * @brief Fonction interne permettant de reconstruire le chemin
 *        lorsqu'un but est atteint.
 * @param came_from Tableau 2D indiquant le parent de chaque cellule.
 * @param current Nœud qui correspond à l'objectif atteint.
 * @param start Nœud de départ pour reconstruire jusqu'au début.
 * @return Un vecteur de Node représentant le chemin complet.
 */
static std::vector<Node> reconstructPath(
    const std::vector<std::vector<std::pair<int, int>>> &came_from,
    Node current,
    const Node &start)
{
    std::vector<Node> path;
    while (!(current == start)) // on utilise l'opérateur == défini dans Node
    {
        path.push_back(current);
        auto [px, py] = came_from[current.x][current.y];
        current.x = px;
        current.y = py;
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Node> AStar::findPath(const std::vector<std::vector<int>> &grid, Node start, Node goal)
{
    if (grid.empty() || grid[0].empty())
    {
        return {};
    }

    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());

    // g_score : coût réel pour atteindre chaque cellule
    std::vector<std::vector<double>> g_score(rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));

    // came_from : tableau 2D stockant le parent (x, y) de chaque case
    std::vector<std::vector<std::pair<int, int>>> came_from(
        rows, std::vector<std::pair<int, int>>(cols, std::make_pair(-1, -1)));

    // Priority queue (min-heap) utilisant l'opérateur >
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;

    // Initialisation du nœud de départ
    start.g_cost = 0.0;
    start.h_cost = calculateHeuristic(start.x, start.y, goal.x, goal.y);
    g_score[start.x][start.y] = 0.0;
    openList.push(start);

    // Définition des 8 directions possibles (orthogonales + diagonales)
    static const std::vector<std::pair<int, int>> DIRECTIONS = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

    // Boucle principale
    while (!openList.empty())
    {
        Node current = openList.top();
        openList.pop();

        // Vérifier si nous avons atteint l'objectif
        if (current.x == goal.x && current.y == goal.y)
        {
            return reconstructPath(came_from, current, start);
        }

        // Vérification s'il existe déjà un meilleur chemin pour ce nœud
        if (current.g_cost > g_score[current.x][current.y])
        {
            continue;
        }

        // Parcours des voisins
        for (auto [dx, dy] : DIRECTIONS)
        {
            int newX = current.x + dx;
            int newY = current.y + dy;

            // Validation des coordonnées et obstacle
            if (!isValid(newX, newY, grid))
            {
                continue;
            }

            // Calcul du coût provisoire
            double tentativeGScore = current.g_cost + grid[newX][newY];

            // Mise à jour si un meilleur chemin est trouvé
            if (tentativeGScore < g_score[newX][newY])
            {
                came_from[newX][newY] = {current.x, current.y};
                g_score[newX][newY] = tentativeGScore;

                Node neighbor;
                neighbor.x = newX;
                neighbor.y = newY;
                neighbor.g_cost = tentativeGScore;
                neighbor.h_cost = calculateHeuristic(newX, newY, goal.x, goal.y);

                openList.push(neighbor);
            }
        }
    }

    // Aucun chemin n'a été trouvé
    return {};
}

bool AStar::isValid(int x, int y, const std::vector<std::vector<int>> &grid) const
{
    return (x >= 0 && y >= 0 &&
            x < static_cast<int>(grid.size()) &&
            y < static_cast<int>(grid[0].size()) &&
            grid[x][y] == 0);
}

double AStar::calculateHeuristic(int x1, int y1, int x2, int y2) const
{
    // Distance euclidienne
    double dx = static_cast<double>(x2 - x1);
    double dy = static_cast<double>(y2 - y1);
    return std::sqrt(dx * dx + dy * dy);
}