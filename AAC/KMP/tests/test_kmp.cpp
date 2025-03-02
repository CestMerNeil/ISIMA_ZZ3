#include "KMP.h"
#include <iostream>
#include <vector>
#include <cassert>

void test_single_occurrence() {
    KMP kmp("abc");
    std::vector<size_t> result = kmp.search("abcabc");
    assert(result == std::vector<size_t>({0, 3}));
    std::cout << "test_single_occurrence réussi." << std::endl;
}

void test_multiple_occurrences() {
    KMP kmp("abc");
    std::vector<size_t> result = kmp.search("abcabcabc");
    assert(result == std::vector<size_t>({0, 3, 6}));
    std::cout << "test_multiple_occurrences réussi." << std::endl;
}

void test_no_occurrence() {
    KMP kmp("abc");
    std::vector<size_t> result = kmp.search("defdefdef");
    assert(result.empty());
    std::cout << "test_no_occurrence réussi." << std::endl;
}

void test_partial_overlap() {
    KMP kmp("aab");
    std::vector<size_t> result = kmp.search("aaab");
    assert(result == std::vector<size_t>({1}));
    std::cout << "test_partial_overlap réussi." << std::endl;
}

void test_case_insensitive() {
    KMP kmp("abc", true);
    std::vector<size_t> result = kmp.search("ABCabc");
    assert(result == std::vector<size_t>({0, 3}));
    std::cout << "test_case_insensitive réussi." << std::endl;
}

void test_regex_search() {
    KMP kmp("a.c");
    std::vector<size_t> result = kmp.searchWithRegex("abcadc");
    assert(result == std::vector<size_t>({0, 3}));
    std::cout << "test_regex_search réussi." << std::endl;
}

void test_regex_search_multiple() {
    KMP kmp("a.c");
    std::vector<size_t> result = kmp.searchWithRegex("abcadcabc");
    assert(result == std::vector<size_t>({0, 3, 6}));
    std::cout << "test_regex_search_multiple réussi." << std::endl;
}

int main() {
    test_single_occurrence();
    test_multiple_occurrences();
    test_no_occurrence();
    test_partial_overlap();
    test_case_insensitive();
    test_regex_search();
    test_regex_search_multiple();
    std::cout << "Tous les tests ont réussi" << std::endl;
    return 0;
}
