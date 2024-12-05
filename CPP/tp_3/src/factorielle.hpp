#ifndef FACTORIELLE_HPP
#define FACTORIELLE_HPP

template <unsigned int N>
struct Factorielle
{
    static const unsigned long valeur = N * Factorielle<N - 1>::valeur;
};

template <>
struct Factorielle<0>
{
    static const unsigned long valeur = 1;
};

#endif // FACTORIELLE_HPP