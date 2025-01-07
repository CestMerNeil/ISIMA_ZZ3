/**
 * @file status.hpp
 * @brief CLHEP random number generator status functions
 *
 * @author Ao XIE
 * @date Dec 2024
 * @version 1.0
 * @note C++17
 *
 * This file contains the functions to store, restore and generate status for the CLHEP random number generator.
 */
#pragma once

#include "CLHEP/Random/MTwistEngine.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>
#include <mutex>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

static std::mutex status_mutex;

/**
 * @brief Store the status of the CLHEP random number generator
 *
 * @param state_name The name of the status file
 * @param times The number of random numbers to generate
 * @param seed The seed of the random number generator
 *
 * @return void
 */
void storeStatus(std::string &state_name, long long times, int seed = 420116)
{
    std::lock_guard<std::mutex> lock(status_mutex);
    CLHEP::MTwistEngine engine(seed);
    engine.saveStatus(("data/" + state_name).c_str());
}

/**
 * @brief Restore the status of the CLHEP random number generator
 *
 * @param state_name The name of the status file
 * @return CLHEP::MTwistEngine
 */
CLHEP::MTwistEngine restoreStatus(std::string &state_name)
{
    CLHEP::MTwistEngine engine;
    engine.restoreStatus(("data/" + state_name).c_str());
    return engine;
}

// BYE~ Damn thing's taking up all my storage space.
// ¯\_(ツ)_/¯
/**
 * @brief Generate random numbers using the CLHEP random number generator and store them in a file
 *
 * @param state_name The name of the status file
 * @param times The number of random numbers to generate
 * @param seed The seed of the random number generator
 *
 * @return void
 */
void generateStatus(std::string &state_name, long long times, int seed = 420116)
{
    CLHEP::MTwistEngine engine(seed);
    engine.saveStatus(("data/" + state_name).c_str());
    std::ofstream ofs(("data/" + state_name + "_random-numbers.bin").c_str());
    if (!ofs.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    const long long update_freq = times / 100;

    for (long long i = 0; i < times; ++i)
    {
        double r = engine.flat();
        ofs << std::setprecision(17) << r << "\n";

        if (i % update_freq == 0 || i == times - 1)
        {
            double progress = static_cast<double>(i + 1) / times;
            int pos = static_cast<int>(50 * progress);

            std::cout << "\r[CLHEP Generate] [";
            for (int j = 0; j < 50; ++j)
            {
                if (j < pos)
                    std::cout << "=";
                else if (j == pos && i + 1 < times)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << std::fixed << std::setprecision(1)
                      << (progress * 100.0f) << "%" << std::flush;
        }
    }
    ofs.close();
}

/**
 * @brief Test the status of the CLHEP random number generator
 *
 * @param state_name The name of the status file
 * @param times The number of random numbers to generate
 *
 * @return void
 */
void restoreStatus_test(std::string &state_name, long long times)
{
    CLHEP::MTwistEngine engine;
    engine.restoreStatus(("data/" + state_name).c_str());
    std::ifstream ifs(("data/" + state_name + "_random-numbers.bin").c_str());
    if (!ifs.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    long long count = 0;
    double val;
    while (count < times && (ifs >> val))
    {
        double new_val = engine.flat();
        std::cout << std::setprecision(17) << std::endl;
        if (new_val == val)
        {
            std::cout << GREEN << val << " ✅" << RESET << std::endl;
        }
        else
        {
            std::cout << RED << val << " ❌" << new_val << RESET << std::endl;
        }
        count++;
    }
}