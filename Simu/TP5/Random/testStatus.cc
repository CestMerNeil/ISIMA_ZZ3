#include "CLHEP/Random/MTwistEngine.h"
#include <iostream>
#include <iomanip>
#include <cmath> // fabs

int main()
{
    CLHEP::MTwistEngine engine(12345);
    engine.saveStatus("mt_state");

    double numbers[10];
    for (int i = 0; i < 10; i++)
    {
        numbers[i] = engine.flat();
        std::cout << std::setprecision(17) << numbers[i] << std::endl;
    }

    engine.restoreStatus("mt_state");

    for (int i = 0; i < 10; i++)
    {
        double restored = engine.flat();
        std::cout << std::setprecision(10)
                  << restored << " (Expected: "
                  << numbers[i] << ")";

        if (std::fabs(restored - numbers[i]) < 1e-14)
            std::cout << " ✓";
        else
            std::cout << " ×";

        std::cout << std::endl;
    }

    return 0;
}