
#include <iostream>
#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>
#include <optlib/Points/SetOfPoints/PointVals/PointVal.h>
#include <optlib/Points/SetOfPoints/PointVals/PointValOperators.h>

using namespace OptLib;

int main() try
{
    Point<3> rp6{2.0, 1.0, 3.0};
    auto rp16{1.0 - rp6};

   // testting PointVal ctors
    auto pv1{PointVal<3>{rp16 + 8.0, 1.0}};
    auto pv2{pv1};
    auto pv33{PointVal<3>{Point<3>{}, 1.0}};

    // testing PointVal operators
    auto pv3{pv1 + pv2};
    std::cout << pv3 << std::endl;

    auto pv4{sqrt(abs(pv1))};

    auto pv5{pv3 / pv4};

    return 0;
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}