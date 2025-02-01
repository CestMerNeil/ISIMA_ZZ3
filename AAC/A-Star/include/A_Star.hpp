#pragma once

#include <vector>
#include <cmath>
#include <utility>

/**
 * @struct Node
 * @brief Structure représentant un nœud de la grille,
 *        incluant ses coordonnées et ses coûts (g, h).
 */
struct Node
{
    int x;
    int y;
    double g_cost = 0.0; ///< Coût déjà parcouru (distance depuis le départ)
    double h_cost = 0.0; ///< Heuristique (distance estimée jusqu'au but)
    int parent_x = -1;   ///< Coordonnée x du parent (non utilisée directement ici)
    int parent_y = -1;   ///< Coordonnée y du parent (non utilisée directement ici)

    /**
     * @brief Retourne la somme des coûts g et h.
     * @return f = g_cost + h_cost.
     */
    double f_cost() const
    {
        return g_cost + h_cost;
    }

    /**
     * @brief Opérateur de comparaison strictement supérieur basé sur f_cost.
     *        Utilisé dans les priority_queue pour donner la priorité au plus petit f_cost().
     */
    bool operator>(const Node &other) const
    {
        return f_cost() > other.f_cost();
    }

    /**
     * @brief Opérateur d'égalité pour comparer deux Node par leurs coordonnées.
     * @param other Le nœud à comparer.
     * @return true si (x,y) sont identiques, false sinon.
     */
    bool operator==(const Node &other) const
    {
        return (x == other.x && y == other.y);
    }
};

/**
 * @class AStar
 * @brief Classe implémentant l'algorithme A* pour trouver un chemin.
 */
class AStar
{
public:
    /**
     * @brief Trouve un chemin entre start et goal dans la grille.
     * @param grid Matrice d'entiers (0 = libre, 1 = obstacle).
     * @param start Nœud de départ.
     * @param goal Nœud d'arrivée.
     * @return Un vecteur de Node représentant le chemin (vide si aucun chemin).
     */
    std::vector<Node> findPath(const std::vector<std::vector<int>> &grid, Node start, Node goal);

private:
    /**
     * @brief Vérifie si la position (x, y) est valide dans la grille
     *        et qu'elle n'est pas un obstacle.
     * @param x Coordonnée x.
     * @param y Coordonnée y.
     * @param grid La grille (matrice d'entiers).
     * @return true si la case est libre et dans les bornes, false sinon.
     */
    bool isValid(int x, int y, const std::vector<std::vector<int>> &grid) const;

    /**
     * @brief Calcule l'heuristique (distance euclidienne) entre deux points.
     * @param x1 Coordonnée x du nœud courant.
     * @param y1 Coordonnée y du nœud courant.
     * @param x2 Coordonnée x du but.
     * @param y2 Coordonnée y du but.
     * @return Distance euclidienne entre (x1, y1) et (x2, y2).
     */
    double calculateHeuristic(int x1, int y1, int x2, int y2) const;
};