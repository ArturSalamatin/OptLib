#ifndef POINTVAL_H
#define POINTVAL_H

#include "Point/Point.h"

namespace OptLib
{
    /// <summary>
    /// @brief Aggregates Point with associated Value. 
    /// Essentially a {Point, Val}-pair with a comparator to sort Points
    /// </summary>
    template <size_t dim>
    struct PointVal
    {
        Point<dim> P;
        double Val;

        PointVal() = default;
        PointVal(const PointVal&) = default;
        PointVal(PointVal&&) noexcept = default;
        PointVal<dim>& operator=(const PointVal&) noexcept = default;
        PointVal<dim>& operator=(PointVal&&) noexcept = default;

        template<typename T>
        PointVal(T&&P, double Val) : P{std::forward<T>(P)}, Val{Val}
        {
        }
        
        PointVal(const Point<dim> &P, double Val) : P{P}, Val{Val}
        {
        }

        auto operator[](size_t i) const
        {
            return P[i];
        }

    };
}

#endif