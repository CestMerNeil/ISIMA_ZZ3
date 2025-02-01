#include <iostream>
#include <cassert>
#include "A_Star.hpp"
#include "Grid.hpp"

/**
 * @brief Test 1 : Chemin simple sur une grille vide 5x5.
 */
void testSimplePath()
{
    Grid grille(5, 5);
    AStar astar;

    std::vector<Node> chemin = astar.findPath(grille.getGrid(), {0, 0}, {4, 4});
    // Vérification : chemin non vide
    assert(!chemin.empty());

    // Vérification : premier et dernier nœud
    assert((chemin.front() == Node{0, 0}));
    assert((chemin.back() == Node{4, 4}));

    std::cout << "[OK] testSimplePath\n";
}

/**
 * @brief Test 2 : Éviter les obstacles dans une grille 5x5.
 */
void testAvoidObstacles()
{
    Grid grille(5, 5);
    // Ajout d'obstacles
    grille.ajouterObstacle(1, 1);
    grille.ajouterObstacle(1, 2);
    grille.ajouterObstacle(1, 3);

    AStar astar;
    std::vector<Node> chemin = astar.findPath(grille.getGrid(), {0, 0}, {4, 4});

    // Vérification : chemin non vide
    assert(!chemin.empty());
    // Vérification : positions de départ et d'arrivée
    assert((chemin.front() == Node{0, 0}));
    assert((chemin.back() == Node{4, 4}));

    std::cout << "[OK] testAvoidObstacles\n";
}

/**
 * @brief Test 3 : Aucun chemin possible, la grille est bloquée
 */
void testNoPath()
{
    Grid grille(3, 3);
    // Ajout d'obstacles
    grille.ajouterObstacle(1, 0);
    grille.ajouterObstacle(1, 1);
    grille.ajouterObstacle(1, 2);

    AStar astar;
    std::vector<Node> chemin = astar.findPath(grille.getGrid(), {0, 0}, {2, 2});

    // Vérification : chemin vide
    assert(chemin.empty());

    std::cout << "[OK] testNoPath\n";
}

/**
 * @brief Point d'entrée pour les tests manuels.
 */
int main()
{
    testSimplePath();
    testAvoidObstacles();
    testNoPath();

    std::cout << "Tous les tests ont été validés avec succès.\n";
    return 0;
}