
#include <iostream>
#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>
#include <optlib/Points/SetOfPoints/PointVals/Point/PointOperators.h>
#include <optlib/Points/SetOfPoints/PointVals/PointVal.h>

#include <optlib/Points/SetOfPoints/SetOfPoints.h>
#include <optlib/Points/SetOfPoints/SetOfPointOperators.h>
#include <optlib/Points/SetOfPointVals.h>

using namespace OptLib;

int main() try
{
    // testing SetOfPoints ctors
    auto sp1{
        SetOfPoints<2, Point<3>>{
            Point<3>{1.0, 2.0, 3.0},
            Point<3>{3.0, 2.0, 1.0}}};

    auto pp1{Point<3>{1.0, 1.0, 1.0}};
    auto out{sp1 * pp1};

    std::cout << sp1 << '\n'
              << pp1 << std::endl;

    auto mean1{sp1.mean()};
    auto [mean2, disp2] = sp1.dispersion();

    // testing SetOfPointVals ctors
    auto rsp{
        RawSetOfPoints<3, PointVal<2>>{
            PointVal<2>{RawPoint<2>{1.0, 1.0}, 2.0},
            PointVal<2>{RawPoint<2>{1.0, 1.0}, 2.0},
            PointVal<2>{RawPoint<2>{1.0, 1.0}, 2.0}}};

    auto sopv{SetOfPointVals<3, PointVal<2>>{rsp}};
    auto sopv2{SetOfPointVals<3, PointVal<2>>{std::move(rsp)}};
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}