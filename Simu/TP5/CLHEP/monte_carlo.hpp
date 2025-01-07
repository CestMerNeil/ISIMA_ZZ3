/**
 * @file monte_carlo.hpp
 * @brief Calculate the volume of a sphere of radius 1 using Monte Carlo methods
 *
 * @author Ao XIE
 * @date Dec 2024
 * @version 1.0
 * @note C++17
 */
#pragma once

#include "status.hpp"
#include <thread>

static std::mutex progress_mutex;

/**
 * @brief Monte Carlo calculation
 *
 * @param state_name The name of the status file
 * @param n The number of random numbers to generate
 * @param batch_size The size of each batch
 *
 * @return Volume of a sphere of radius 1 in double
 */
double Monte_Carlo(std::string &state_name, long long n, int batch_size = 100000)
{
    CLHEP::MTwistEngine engine = restoreStatus(state_name);
    int current_inside = 0;
    int current_count = 0;
    long long batch_count = 0, total_count = 0;
    double sum_ratio = 0.0;
    // const int update_freq = batch_size / 100;
    // double progress = 0.0;
    // int pos = 0;

    while (total_count < n)
    {
        double x = engine.flat();
        double y = engine.flat();
        double z = engine.flat();
        if (x * x + y * y + z * z <= 1.0)
        {
            current_inside++;
        }
        current_count++;
        total_count++;

        // using no longer progress bar
        // if (current_count % update_freq == 0 || total_count == n)
        // {
        //     progress = static_cast<double>(total_count) / n;
        //     pos = static_cast<int>(50 * progress);

        //     {
        //         std::lock_guard<std::mutex> lock(progress_mutex);
        //         std::cout << "\033[K";
        //         std::cout << "    [" << state_name << "] [";
        //         for (int i = 0; i < 50; ++i)
        //         {
        //             if (i < pos)
        //                 std::cout << "=";
        //             else if (i == pos && total_count < n)
        //                 std::cout << ">";
        //             else
        //                 std::cout << " ";
        //         }
        //         std::cout << "] " << std::fixed << std::setprecision(1)
        //                   << (progress * 100.0f) << "%\n"
        //                   << std::flush;
        //     }
        // }

        if (current_count == batch_size)
        {
            sum_ratio += static_cast<double>(current_inside) / current_count;
            batch_count++;
            current_inside = 0;
            current_count = 0;
        }
    }

    if (current_count != 0)
    {
        sum_ratio += static_cast<double>(current_inside) / current_count;
        batch_count++;
    }

    // using no longer progress bar
    // {
    //     std::lock_guard<std::mutex> lock(progress_mutex);
    //     std::cout << "    [" << state_name << "] Completed!\n"
    //               << std::flush;
    // }

    return 8.0 * (sum_ratio / batch_count);
}
