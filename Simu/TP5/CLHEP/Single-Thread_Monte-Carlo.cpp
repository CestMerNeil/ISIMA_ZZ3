/**
 * @file Single-Thread_Monte-Carlo.cpp
 * @brief A single-threaded Monte Carlo simulation to estimate the volume of a sphere with radius 1
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

/**
 * @brief Monte Carlo calculations with single thread
 */
int main()
{
    std::vector<std::string> state_names;
    int seed = 420116;
    int times = 10;
    long long times_test = 2e9;
    double v = 0.0;
    int i = 0;

    for (int i = 0; i < times; ++i)
    {
        state_names.push_back("monte_carlo_data-" + std::to_string(i));
    }

    for (std::string &state_name : state_names)
    {
        std::cout << std::endl;
        std::cout << "[INFO] Generating status for " << state_name << "..." << std::endl;
        storeStatus(state_name, times_test, seed + i);
        ++i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (std::string &state_name : state_names)
    {
        v += Monte_Carlo(state_name, times_test);
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