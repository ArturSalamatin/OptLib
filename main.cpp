#include <iostream>
#include <array>
#include <functional>

#include "Config.h"

#include "src/Points/SetOfPoints/PointVal/Point/Point.h"
#include "src/Points/SetOfPoints/PointVal/Point/PointOperators.h"

#include "src/Points/SetOfPoints/PointVal/PointVal.h"
#include "src/Points/SetOfPoints/PointVal/PointValOperators.h"

#include "src/Points/SetOfPoints/SetOfPoints.h"
#include "src/Points/SetOfPoints/SetOfPointOperators.h"

#include "src/Points/SetOfPointVals.h"

#include "src/Functions/Function.h"
#include "src/Functions/Paraboloid.h"
#include "src/Functions/Himmel.h"
#include "src/Functions/Rozenbrock.h"
#include "src/Functions/FuncAlongGradDirection.h"
#include "src/Functions/FunctionParam.h"

#include "src/States/State.h"

#include "src/Optimizers/OverallOptimizer.h"
#include "src/Optimizers/OneDim/Bisection.h"

using namespace OptLib;

/// @brief program entry point
/// @return code of execution result
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // report version
        std::cout << argv[0] << " Version " << OptLib_VERSION_MAJOR << "."
                  << OptLib_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

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
    auto rp15{1.0 + rp6};
    auto rp16{1.0 - rp6};

    auto dp1{dot_product(rp7, rp8)};
    auto dp2{norm(rp7)};
    auto dp3{dist(rp7, rp8)};

    // testting PointVal ctors
    auto pv1{PointVal<3>{rp16 + 8.0, 1.0}};
    auto pv2{pv1};
    auto pv33{PointVal<3>{Point<3>{}, 1.0}};

    // testing PointVal operators
    auto pv3{pv1 + pv2};
    std::cout << pv3 << std::endl;

    auto pv4{sqrt(abs(pv1))};

    auto pv5{pv3 / pv4};

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

    // testing Function

    ConcreteFunc::Himmel Him{};
    double result1{Him(Point<2>{2.0, 1.0})};
    ConcreteFunc::Rozenbrok Roz{};
    double result2{Roz(Point<2>{2.0, 1.0})};

    ConcreteFunc::FuncAlongGradDirection<2> f{&Him, Point<2>{2.0, 1.0}};
    auto gr{f.grad(Point<1>{3.0})};

    // testing FunctionParam
    auto fp{ConcreteFuncParam::LinearFuncWithGrad{}};
    fp(Point<1>{1.0}, Point<1>{2.0});

    // testing State
    Simplex<1> simpl{Point<1>{1.0}, Point<1>{3.0}};
    ConcreteState::StateSegment state_segm{simpl, &f};

    ConcreteState::StatePoint<3> stp{
        PointVal<3>{
            Point<3>{1.0, 2.0, 4.0},
            5.0}};

    Simplex<3> simpl2{
        Point<3>{1.0, 1.0, 2.5},
        Point<3>{3.0, 2.0, 5.6},
        Point<3>{1.0, 7.0, 2.5},
        Point<3>{12.0, 2.0, 5.6}};

    ConcreteFunc::Paraboloid<3> fpp{
        Hess<3>{
            Point<3>{1.0, 2.0, 3.0},
            Point<3>{1.0, 16.0, 3.0},
            Point<3>{1.0, 2.0, 7.0}}};

    // by copy-ctor
    ConcreteState::StateDirect<3> state_direct{simpl2, &fpp};
    // by move-ctro
    ConcreteState::StateDirect<3> state_direct2{
        Simplex<3>{
            Point<3>{1.0, 1.0, 2.5},
            Point<3>{3.0, 2.0, 5.6},
            Point<3>{1.0, 7.0, 2.5},
            Point<3>{12.0, 2.0, 5.6}},
        &fpp};

    // testing StatePoint
    ConcreteState::StatePoint<3> state{
        PointVal<3>{
            Point<3>{1.0, 2.0, 4.0},
            5.0}};

    // test OverallOptimizer

    ConcreteFunc::Paraboloid<1> parab{Hess<1>{2.0}};

    ConcreteState::StateBisection bisect_state{
        Simplex<1>{
            Point<1>{-2.0},
            Point<1>{2.0}},
        &parab};

    Optimizer<ConcreteState::StateBisection>
        bisect_opt{
            &bisect_state,
            &parab,
            OptimizerParams{1E-5, 1E-5, 300}};
    auto result = bisect_opt.Optimize<ConcreteOptimizer::Bisection>();

    return 0;
}