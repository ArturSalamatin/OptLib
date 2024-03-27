#include <iostream>
#include <array>

#include "src/AuxMethods/Point.h"
#include "src/AuxMethods/Simplex.h"

/// @brief program entry point
/// @return code of execution result
int main()
{
    OptLib::Point<3> P1{};
    OptLib::Point<3> P2{};

    auto it = P1.begin();

    auto result{P1+P2};

    auto r{P1+5.0};

    std::cout << P1[0] << std::endl;
    std::cout << P1 << std::endl;

    return 0;
}