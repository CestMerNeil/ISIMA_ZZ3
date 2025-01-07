/**
 * @file checkStatus.cpp
 * @brief Test the status of the CLHEP random number generator
 *
 * @author Ao XIE
 * @date Dec 2024
 * @version 1.0
 * @note C++17
 */

#include "status.hpp"

/**
 * @brief Generate and test the status of the CLHEP random number generator
 */
int main()
{
    std::string state_name = "10_times_test";
    long long times = 10;
    int seed = 123456;

    generateStatus(state_name, times, seed);
    restoreStatus_test(state_name, times);

    return 0;
}