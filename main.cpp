#include <iostream>
#include <array>

#include "src/AuxMethods/Point/Point.h"
#include "src/AuxMethods/Point/PointOperators.h"
#include "src/AuxMethods/PointVal.h"
#include "src/AuxMethods/PointValOperators.h"

using namespace OptLib;

/// @brief program entry point
/// @return code of execution result
int main()
{
    // testing Point ctors
    auto rp1{Point<3>{1.0, 2.0, 3.0}};
    auto rp2 = rp1;
    auto rp3 = Point<3>{1.0, 2.0, 3.0};
    auto rp4{std::move(rp2)};
    auto rp5 = std::move(rp4);
    Point<3> rp6{2.0, 1.0, 3.0};

    // testing Point operators
    std::cout << rp6 << std::endl;
    rp6 += 3.0;
    rp6 -= 3.0;
    rp6 *= 2.5;
    rp6 /= 2.5;

    auto rp7{rp6 + 1.0};
    auto rp8{rp6 - 1.0};
    auto rp9 = rp6 * 2.0;
    auto rp91 = 2.0 * rp6;
    auto rp10 = rp6 / 2.0;
    auto rp11 = abs(rp6);
    auto rp12 = sqrt(rp6);
    auto rp13 = rp6 / 2.0;
    auto rp14 = rp6 / 2.0;
    auto rp15{1.0+rp6};
    auto rp16{1.0-rp6};

    auto dp1{dot_product(rp7,rp8)};
    auto dp2{norm(rp7)};
    auto dp3{dist(rp7,rp8)};


    // testting PointVal ctors
    auto pv1{PointVal<3>{rp16, 1.0}};
    auto pv2{pv1};

    // testing PointVal operators
    auto pv3{pv1+pv2};
    std::cout << pv3 << std::endl;

    auto pv4{sqrt(pv1)};

    auto pv5{pv3/pv4};

    return 0;
}