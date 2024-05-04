#ifndef SETOFPOINTSOPERATORS_H
#define SETOFPOINTSOPERATORS_H

#include "PointVals/Point/Point.h"
#include "PointVals/Point/PointOperators.h"
#include "SetOfPoints.h"

namespace OptLib
{
    /// <summary>
    /// A matrix*vector multiplication
    /// </summary>
    /// <param name="A"></param>
    /// <param name="B"></param>
    /// <returns></returns>
    template <size_t count, size_t dim>
    Point<count> operator*(
        const SetOfPoints<count, Point<dim>> &A, 
        const Point<dim> &B)
    {
        Point<count> out;
        std::transform(A.cbegin(), A.cend(), out.begin(), 
            [&B](const auto& v)
            {
                return dot_product(v, B);
            });
        return out;
    }

    template <size_t count, typename point, typename Stream>
    auto &operator<<(
        Stream &o,
        const SetOfPoints<count,
                          point> &output)
    {
        static_assert(count > 0);
        o << "{ " << output[0];
        if constexpr (count > 1)
        {
            for (size_t i = 1; i < count; i++)
                o << "; " << output[i];
        }
        o << " }";

        return o;
    }
} // OptLib
#endif