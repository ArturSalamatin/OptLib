#ifndef SETOFPOINTSOPERATORS_H
#define SETOFPOINTSOPERATORS_H

#include "PointVal/Point/Point.h"
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
        for (size_t i = 0; i < dim; ++i)
            out[i] = dot_product(A[i], B);
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