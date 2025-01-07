/**
 * @file algo.c
 * @author Ao XIE
 *
 * @brief Compare the Kahan and neumaier summation algorithms
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mt19937.h"
#include <mpfr.h>

// ANSI for output
// https://en.wikipedia.org/wiki/ANSI_escape_code
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

/**
 * @brief Kahan Summation Algorithm
 *
 * @param arr Array of numbers
 * @param n Number of elements in the array
 * @return double Sum of the array
 */
double kahan(double *arr, int n)
{
    double sum = 0.0;
    double c = 0.0;

    for (int i = 0; i < n; i++)
    {
        double y = arr[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

/**
 * @brief neumaier Summation Algorithm
 *
 * @param arr Array of numbers
 * @param n Number of elements in the array
 * @return double Sum of the array
 */
double neumaier(double *arr, int n)
{
    double sum = 0.0;
    double c1 = 0.0;
    double c2 = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double x = arr[i];
        double y = x - (c1 + c2);
        double t = sum + y;

        if (fabs(x) > 1e6)
        {
            c1 += (sum - t) + y;
        }
        else
        {
            c2 += (y - t) + sum;
        }

        sum = t;
    }

    return sum + c1 + c2;
}

/**
 * @brief Generate random array
 *
 * @param n Number of elements in the array
 * @return double* Array of random numbers
 */
double *generate_random_array(int n)
{
    double *arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++)
    {
        // arr[i] = mt19937_generate_double();
        // BYE BYE, MT Generater is great but not for this test
        arr[i] = (double)rand() / RAND_MAX;
    }
    return arr;
}

/**
 * @brief Generate uniform array
 *
 * @param n Number of elements in the array
 * @param value Value of the array
 * @return double* Array of uniform numbers
 */
double *generate_uniform_array(int n, double value)
{
    double *arr = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        arr[i] = value;
    }
    return arr;
}

/**
 * @brief Generate extreme array
 *
 * @param n Number of elements in the array
 * @param large_value Large value of the array
 * @param small_value Small value of the array
 * @return double* Array of extreme numbers
 */
double *generate_extreme_array(int n, double large_value, double small_value)
{
    double *arr = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (i % 2 == 0) ? large_value : small_value;
    }
    return arr;
}

/**
 * @brief Native Summation Algorithm
 *
 * @param arr Array of numbers
 * @param n Number of elements in the array
 * @return double Sum of the array
 */
double native_sum(double *arr, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

/**
 * @brief MPFR Summation Algorithm
 *
 * @param arr Array of numbers
 * @param n Number of elements in the array
 * @return double High precision sum of the array
 */
double mpfr_sum_IDM(double *arr, int n)
{
    mpfr_t sum, temp;
    mpfr_init2(sum, 256);
    mpfr_init2(temp, 256);

    mpfr_set_d(sum, 0.0, MPFR_RNDN);

    for (int i = 0; i < n; i++)
    {
        mpfr_set_d(temp, arr[i], MPFR_RNDN);
        mpfr_add(sum, sum, temp, MPFR_RNDN);
    }

    double result = mpfr_get_d(sum, MPFR_RNDN);
    mpfr_clear(sum);
    mpfr_clear(temp);

    return result;
}

int main()
{
    srand((unsigned int)time(NULL));

    init_mt19937((uint32_t)time(NULL));
    // Generate dataset
    int n = 1000;
    double *arr = generate_random_array(n);
    double *uniform_arr = generate_uniform_array(n, 0.1);
    // double *extreme_arr = generate_extreme_array(n, mt19937_generate_double(), mt19937_generate_double() * 1e10);
    double *extreme_arr = generate_extreme_array(n, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX * 1e10);

    // Random dataset
    printf(BLUE "====================================================================================\n" RESET);
    printf(BOLD GREEN "Random Dataset\n" RESET);
    printf("Native      Sum: %0.18f\n", native_sum(arr, n));
    printf("Kahan       Sum: %0.18f\n", kahan(arr, n));
    printf("neumaier    Sum: %0.18f\n", neumaier(arr, n));
    printf(BLUE "MPFR        Sum: %0.18f\n" RESET, mpfr_sum_IDM(arr, n));
    printf(RED "Native Error: %0.18f\n" RESET, fabs(native_sum(arr, n) - mpfr_sum_IDM(arr, n)));
    printf(RED "Kahan Error: %0.18f\n" RESET, fabs(kahan(arr, n) - mpfr_sum_IDM(arr, n)));
    printf(RED "neumaier Error: %0.18f\n" RESET, fabs(neumaier(arr, n) - mpfr_sum_IDM(arr, n)));

    // Uniform dataset
    printf(BLUE "====================================================================================\n" RESET);
    printf(BOLD GREEN "Uniform Dataset\n" RESET);
    printf("Native      Sum: %0.18f\n", native_sum(uniform_arr, n));
    printf("Kahan       Sum: %0.18f\n", kahan(uniform_arr, n));
    printf("neumaier    Sum: %0.18f\n", neumaier(uniform_arr, n));
    printf(BLUE "MPFR        Sum: %0.18f\n" RESET, mpfr_sum_IDM(uniform_arr, n));
    printf(RED "Native Error: %0.18f\n" RESET, fabs(native_sum(uniform_arr, n) - mpfr_sum_IDM(uniform_arr, n)));
    printf(RED "Kahan Error: %0.18f\n" RESET, fabs(kahan(uniform_arr, n) - mpfr_sum_IDM(uniform_arr, n)));
    printf(RED "neumaier Error: %0.18f\n" RESET, fabs(neumaier(uniform_arr, n) - mpfr_sum_IDM(uniform_arr, n)));

    // Extreme dataset
    printf(BLUE "====================================================================================\n" RESET);
    printf(BOLD GREEN "Extreme Dataset\n" RESET);
    printf("Native      Sum: %0.18f\n", native_sum(extreme_arr, n));
    printf("Kahan       Sum: %0.18f\n", kahan(extreme_arr, n));
    printf("neumaier    Sum: %0.18f\n", neumaier(extreme_arr, n));
    printf(BLUE "MPFR        Sum: %0.18f\n" RESET, mpfr_sum_IDM(extreme_arr, n));
    printf(RED "Native Error: %0.18f\n" RESET, fabs(native_sum(extreme_arr, n) - mpfr_sum_IDM(extreme_arr, n)));
    printf(RED "Kahan Error: %0.18f\n" RESET, fabs(kahan(extreme_arr, n) - mpfr_sum_IDM(extreme_arr, n)));
    printf(RED "neumaier Error: %0.18f\n" RESET, fabs(neumaier(extreme_arr, n) - mpfr_sum_IDM(extreme_arr, n)));

    return 0;
}