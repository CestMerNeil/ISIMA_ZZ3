#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>
#include <regex>

/**
 * @class KMP
 * @brief algorithme de recherche de motifs Knuth-Morris-Pratt (KMP).
 */
class KMP {
public:
    /**
     * @brief Construit un objet KMP avec le motif spécifié.
     * @param pattern Le motif à rechercher.
     * @param caseInsensitive Active ou non la recherche insensible à la casse.
     */
    explicit KMP(const std::string& pattern, bool caseInsensitive = false);

    /**
     * @brief Recherche toutes les occurrences du motif dans un texte.
     * @param text Le texte dans lequel on fait la recherche.
     */
    std::vector<size_t> search(const std::string& text) const;

    /**
     * @brief Recherche à l'aide d'un motif d'expression régulière (Regex).
     * @param text Le texte dans lequel on fait la recherche.
     */
    std::vector<size_t> searchWithRegex(const std::string& text) const;

private:
    std::string pattern_;      // Le motif à rechercher.
    std::vector<size_t> lps_;  // Le tableau des préfixes et suffixes les plus longs.
    bool caseInsensitive_;     // Recherche insensible à la casse.

    /**
     * @brief Calcule le tableau LPS pour le motif.
     */
    void computeLPSArray();
};

#endif
