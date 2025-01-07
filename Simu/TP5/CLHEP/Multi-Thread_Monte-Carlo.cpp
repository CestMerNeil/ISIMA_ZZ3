/**
 * @file Multi-Thread_Monte-Carlo.cpp
 * @brief Calculate the volume of a sphere with radius 1 using the Monte Carlo method with multiple threads
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
#include <thread>

/**
 * @brief Monte Carlo calculations on a single thread
 *
 * @param state_name The name of the status file
 * @param n The number of random numbers to generate
 * @param v The volume of the sphere in double
 * @param seed The seed of the random number generator
 */
void Monte_Carlo_Thread(std::string &state_name, long long n, double &v, int seed = 420116)
{
    storeStatus(state_name, n, seed);
    v = Monte_Carlo(state_name, n);
}

/**
 * @brief Monte Carlo calculations with multi threads
 */
int main()
{
    int seed = 420116;
    int times = 10;
    long long times_test = 2e9;
    std::vector<std::string> state_names;
    std::vector<double> volumes(times, 0.0);
    std::vector<std::thread> threads;

    threads.reserve(times);
    state_names.reserve(times);

    for (int i = 0; i < times; ++i)
    {
        state_names.push_back("multi_monte_carlo_data-" + std::to_string(i));
        storeStatus(state_names[i], times_test, seed + i);
        ++i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < times; ++i)
    {
        threads.push_back(std::thread(Monte_Carlo_Thread,
                                      std::ref(state_names[i]),
                                      times_test,
                                      std::ref(volumes[i]),
                                      seed));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    double v = 0.0;
    for (double &vol : volumes)
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
}