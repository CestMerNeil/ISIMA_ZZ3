#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

/**
 * @brief Valide si le string n'est pas vide.
 * @param str La string à valider.
 * @param name Le nom du paramètre poursavoir lequel est vide.
 */
void validateNotEmpty(const std::string& str, const std::string& name);

/**
 * @brief Affiche les occurrences du motif dans le texte.
 * @param occurrences Vecteur contenant les indices de départ des correspondances du motif.
 */
void displayOccurrences(const std::vector<size_t>& occurrences);

#endif
