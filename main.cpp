#include <iostream>
#include <array>

#include "src/AuxMethods/Point.h"
#include "src/AuxMethods/Simplex.h"
#include "src/AuxMethods/PointVal.h"

using namespace OptLib;

/// @brief program entry point
/// @return code of execution result
int main()
{
    auto rp1{Point<3>{1.0, 2.0, 3.0}};
    auto rp2 = rp1;
    auto rp3 = Point<3>{1.0, 2.0, 3.0};
    auto rp4{std::move(rp2)};
    auto rp5 = std::move(rp4);
    Point<3> rp6{2.0, 1.0, 3.0};






    RawPoint<3> P0{1.0,1.0,1.0};
    Point<3> P1{};
    Point<3> P2{};
    auto ar{RawPoint<3>{{1.0,1.0,1.0}}};




    Point<3> ar2{1.0,1.0,1.0};

    Point<3> P3{ar};

    auto it = P1.begin();

    auto result{P1+P2};

    auto r{P1+5.0};

    std::cout << P1[0] << std::endl;
    std::cout << P1 << std::endl;

    PointVal<3> Pv1{{2.0, 3.0, 5.0}, 4.0};

    return 0;
}