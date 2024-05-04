#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "SetOfPoints/PointVals/Point/Point.h"
#include "SetOfPoints/PointVals/PointVal.h"
#include "SetOfPoints/SetOfPoints.h"
#include "SetOfPointVals.h"

namespace OptLib
{
    template <size_t dim>
    using SimplexValNoSort = SetOfPointVals<dim + 1, PointVal<dim>>;

    template <size_t dim>
    using Simplex = SetOfPoints<dim + 1, Point<dim>>;
    
    template <size_t dim>
    using SimplexVal = SetOfPoints<dim + 1, PointVal<dim>>;

    using Segment = SimplexValNoSort<1>;

    template <size_t dim>
    using SimplexValSort = SetOfPointValsSort<dim + 1, PointVal<dim>>;
}
#endif