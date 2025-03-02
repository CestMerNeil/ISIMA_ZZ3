#include "KMP.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

KMP::KMP(const std::string &pattern, bool caseInsensitive)
    : pattern_(pattern), caseInsensitive_(caseInsensitive)
{
    if (pattern_.empty())
    {
        throw std::invalid_argument("Pattern cannot be empty.");
    }
    if (caseInsensitive_)
    {
        std::transform(pattern_.begin(), pattern_.end(), pattern_.begin(), ::tolower);
    }
    computeLPSArray();
}

void KMP::computeLPSArray()
{
    size_t length = 0;
    lps_.resize(pattern_.size());
    lps_[0] = 0;
    size_t i = 1;

    while (i < pattern_.size())
    {
        if (pattern_[i] == pattern_[length])
        {
            length++;
            lps_[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps_[length - 1];
            }
            else
            {
                lps_[i] = 0;
                i++;
            }
        }
    }
}

std::vector<size_t> KMP::search(const std::string &text) const
{
    if (text.empty())
    {
        throw std::invalid_argument("Text cannot be empty.");
    }

    std::string searchText = text;
    if (caseInsensitive_)
    {
        std::transform(searchText.begin(), searchText.end(), searchText.begin(), ::tolower);
    }

    std::vector<size_t> occurrences;
    size_t i = 0;
    size_t j = 0;

    while (i < searchText.size())
    {
        if (pattern_[j] == searchText[i])
        {
            i++;
            j++;
        }

        if (j == pattern_.size())
        {
            occurrences.push_back(i - j);
            j = lps_[j - 1];
        }
        else if (i < searchText.size() && pattern_[j] != searchText[i])
        {
            if (j != 0)
            {
                j = lps_[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return occurrences;
}

std::vector<size_t> KMP::searchWithRegex(const std::string &text) const
{
    if (text.empty())
    {
        throw std::invalid_argument("Text cannot be empty.");
    }

    std::regex re(pattern_);
    std::sregex_iterator begin(text.begin(), text.end(), re), end;
    std::vector<size_t> occurrences;

    for (auto it = begin; it != end; ++it)
    {
        occurrences.push_back(it->position());
    }

    return occurrences;
}
