#ifndef POINTVALOPERATORS_H
#define POINTVALOPERATORS_H

#include <tuple>
#include <cassert>

#include "PointVal.h"
#include "Point/PointOperators.h"

namespace OptLib
{
    template <size_t dim, typename Stream>
    auto& operator<<(Stream &o, const PointVal<dim> &r)
    {
        return o << "{ " << r.P << ", " << r.Val << " }";
    }

    template <size_t dim>
    auto operator<(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        return lhs.Val < rhs.Val;
    }

    template <size_t dim>
    auto operator+(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        return PointVal<dim>{lhs.P + rhs.P, lhs.Val + rhs.Val};
    }

    /// elementwise subtraction of vector - vector
    template <size_t dim>
    auto operator-(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        return PointVal<dim>{lhs.P - rhs.P, lhs.Val - rhs.Val};
    }
    /// elementwise multiplication of vector * vector
    template <size_t dim>
    auto operator*(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        return PointVal<dim>{lhs.P * rhs.P, lhs.Val * rhs.Val};
    }
    template <size_t dim>
    auto operator*(const PointVal<dim>& p, double val)
    {
        return PointVal<dim>{p.P * val, p.Val * val};
    }
    /// elementwise division of vector / vector
    template <size_t dim>
    auto operator/(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        assert(rhs.Val != 0);
        assert(
            std::none_of(
                rhs.P.cbegin(), rhs.P.cend(), 
                [](double x) 
                {
                    return x == 0.0;
                }
            )
        );
        return PointVal<dim>{lhs.P / rhs.P, lhs.Val / rhs.Val};
    }
    /// elementwise division vector / scalar
    template <size_t dim>
    auto operator/(PointVal<dim> arr, double val)
    {
        assert(val != 0);
        return PointVal<dim>{arr.P / val, arr.Val / val};
    }

    ///  elementwise sqrt
    template <size_t dim>
    auto sqrt(const PointVal<dim> &p)
    {
        assert(p.Val >= 0.0);
        assert(
            std::none_of(
                p.P.cbegin(), 
                p.P.cend(), 
                [](double x) 
                {
                    return x < 0.0;
                }
            )
        ); 
        return PointVal<dim>{sqrt<dim>(p.P), std::sqrt(p.Val)};
    }
    ///  elementwise abs
    template <size_t dim>
    auto abs(const PointVal<dim> &p)
    {
        return PointVal<dim>{abs(p.P), std::abs(p.Val)};
    }

    /// <summary>
    /// coefficient of variation, mean/variance
    /// </summary>
    /// <typeparam name="point"></typeparam>
    /// <param name="avg"></param>
    /// <param name="disp"></param>
    /// <returns></returns>
    template <typename point>
    auto var_coef(const point &avg, const point &disp)
    { // requires sqrt(vector), abs(vector), vector/vector
        auto disp0{sqrt(disp)};
        return std::pair{disp0 / abs(avg), disp0};
    }
} // OptLib


#endif