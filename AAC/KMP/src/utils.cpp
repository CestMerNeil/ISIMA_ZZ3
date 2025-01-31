#include "utils.h"
#include <iostream>
#include <stdexcept>

void validateNotEmpty(const std::string& str, const std::string& name) {
    if (str.empty()) {
        throw std::invalid_argument(name + " cannot be empty.");
    }
}

void displayOccurrences(const std::vector<size_t>& occurrences) {
    if (!occurrences.empty()) {
        std::cout << "Pattern found at indices: ";
        for (size_t index : occurrences) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Pattern not found in the text." << std::endl;
    }
}
