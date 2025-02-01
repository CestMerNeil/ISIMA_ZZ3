#pragma once

#include <vector>
#include <iostream>
#include "A_Star.hpp"

/**
 * @class Grid
 * @brief Représente la grille utilisée par l'algorithme A*.
 */
class Grid
{
public:
    /**
     * @brief Constructeur de la classe Grid.
     * @param rows Nombre de lignes de la grille.
     * @param cols Nombre de colonnes de la grille.
     */
    Grid(int rows, int cols);

    /**
     * @brief Ajoute un obstacle à la position spécifiée (x, y).
     * @param x Coordonnée x de l'obstacle.
     * @param y Coordonnée y de l'obstacle.
     */
    void ajouterObstacle(int x, int y);

    /**
     * @brief Retourne la grille sous forme d'une matrice d'entiers.
     * @return Référence constante vers la matrice interne de la grille.
     */
    const std::vector<std::vector<int>> &getGrid() const;

    /**
     * @brief Affiche la grille et le chemin calculé (si fourni).
     * @param grid La grille (matrice d'entiers).
     * @param path Le chemin calculé par l'algorithme A*.
     */
    void displayGrid(const std::vector<std::vector<int>> &grid, const std::vector<Node> &path);

private:
    /**
     * @brief Matrice interne représentant la grille.
     */
    std::vector<std::vector<int>> grid;
};