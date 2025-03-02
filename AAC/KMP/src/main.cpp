#include "KMP.h"
#include "utils.h"
#include <iostream>

int main() {
    try {
        std::string texte;
        std::string motif;

        std::cout << "Entrez le texte : ";
        std::getline(std::cin, texte);
        std::cout << "Entrez le motif : ";
        std::getline(std::cin, motif);

        validateNotEmpty(texte, "Texte");
        validateNotEmpty(motif, "Motif");

        bool rechercheInsensible = false;
        std::cout << "Activer la recherche insensible à la casse ? (1 pour oui, 0 pour non) : ";
        std::cin >> rechercheInsensible;

        bool utiliserRegex = false;
        std::cout << "Utiliser la recherche regex ? (1 pour oui, 0 pour non) : ";
        std::cin >> utiliserRegex;

        KMP kmp(motif, rechercheInsensible);
        std::vector<size_t> resultat;

        if (utiliserRegex) {
            resultat = kmp.searchWithRegex(texte);
        } else {
            resultat = kmp.search(texte);
        }

        displayOccurrences(resultat);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
