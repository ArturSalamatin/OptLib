#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "SetOfPoints/PointVal/Point/Point.h"
#include "SetOfPoints/PointVal/PointVal.h"
#include "SetOfPoints/SetOfPoints.h"
#include "SetOfPointVals.h"

namespace OptLib
{
    template <size_t dim>
    using SimplexValNoSort = SetOfPointVals<dim + 1, PointVal<dim>>;

    using Segment = SimplexValNoSort<1>;

    template <size_t dim>
    using SimplexValSort = SetOfPointValsSort<dim + 1, PointVal<dim>>;

    template <size_t dim>
    using Grad = Point<dim>;

    template <size_t dim>
    using Hess = SetOfPoints<dim, Point<dim>>;
}
#endif