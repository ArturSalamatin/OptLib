
#include <iostream>
#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>

#include <optlib/Functions/Paraboloid.h>

#include "optlib/Optimizers/OverallOptimizer.h"
#include "optlib/Optimizers/OneDim/Bisection.h"

using namespace OptLib;

int main() try
{
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
}
catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
}