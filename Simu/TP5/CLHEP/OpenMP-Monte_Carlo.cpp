/**
 * @file OpenMP-Monte_Carlo.cpp
 * @brief Calculate the volume of a sphere with radius 1 using the Monte Carlo method with OpenMP
 *
 * @author Ao XIE
 * @date Dec 2024
 * @version 1.0
 * @note C++17
 */
#include "status.hpp"
#include "monte_carlo.hpp"
#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include <omp.h>

/**
 * @brief Monte Carlo calculations with OpenMP
 */
int main()
{
    int seed = 420116;
    int times = 10;
    long long times_test = 2e9;
    std::vector<std::string> state_names;
    std::vector<double> volumes(times, 0.0);

    state_names.reserve(times);

    for (int i = 0; i < times; ++i)
    {
        state_names.push_back("openmp_monte_carlo_data-" + std::to_string(i));
    }

    std::cout << "System Information:\n";
    std::cout << "Available processors: " << omp_get_num_procs() << std::endl;
    std::cout << "Maximum threads: " << omp_get_max_threads() << std::endl;

#pragma omp parallel for
    for (int i = 0; i < times; ++i)
    {
        storeStatus(state_names[i], times_test, seed + i);
    }

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < times; ++i)
    {
        volumes[i] = Monte_Carlo(state_names[i], times_test);
    }

    double v = 0.0;
    for (const double &vol : volumes)
    {
        v += vol;
    }
    v /= times;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\n----------------------------------------\n";
    std::cout << GREEN << "The volume of the sphere is: " << std::setprecision(17) << v << RESET << std::endl;
    std::cout << RED << "Time taken: " << elapsed.count() << "s" << RESET << std::endl;
    std::cout << "----------------------------------------\n";

    return 0;
}