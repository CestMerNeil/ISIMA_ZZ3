#ifndef EXPONENTIELLE_HPP
#define EXPONENTIELLE_HPP

template <int N>
struct Exponentielle
{
    static const double valeur(double x)
    {
        return 1 + x / N * Exponentielle<N - 1>::valeur(x);
    }
};

template <>
struct Exponentielle<0>
{
    static const double valeur(double x)
    {
        return 1;
    }
};

#endif // EXPONENTIELLE_HPP