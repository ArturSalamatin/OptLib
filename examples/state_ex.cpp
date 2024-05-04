
#include <iostream>

#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>
#include <optlib/Points/SetOfPoints/PointVals/PointValOperators.h>
#include <optlib/Points/Definitions.h>

#include <optlib/States/State.h>

#include <optlib/Functions/Himmel.h>
#include <optlib/Functions/FuncAlongGradDirection.h>
#include <optlib/Functions/Paraboloid.h>

using namespace OptLib;

int main() try
{
     // testing Function
    ConcreteFunc::Himmel Him{};
    double result1{Him(Point<2>{2.0, 1.0})};
    ConcreteFunc::FuncAlongGradDirection<2> f{&Him, Point<2>{2.0, 1.0}};

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
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}