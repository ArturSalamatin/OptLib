#ifndef POINTVAL_H
#define POINTVAL_H

#include <iostream>

#include "Point/Point.h"
#include "Point/PointOperators.h"

namespace OptLib
{
    /// <summary>
    /// @brief Point with associated Value. Essentially a {Point, Val}-pair with a comparator to sort Points
    /// </summary>
    template <size_t dim>
    struct PointVal
    {
        Point<dim> P;
        double Val;

        PointVal() = default;
        PointVal(const PointVal&) = default;
        template<typename T>
        PointVal(T&&P, double Val) : P{std::forward<T>(P)}, Val{Val}
        {
        }
        PointVal(const Point<dim> &P, double Val) : P{P}, Val{Val}
        {
        }
    };

    template <size_t dim>
    bool operator<(const PointVal<dim> &lhs, const PointVal<dim> &rhs)
    {
        return lhs.Val < rhs.Val;
    }

    template <size_t dim>
    PointVal<dim> operator+(const PointVal<dim> &arr1, const PointVal<dim> &arr2)
    {
        return PointVal<dim>{arr1.P + arr2.P, arr1.Val + arr2.Val};
    }

    /// elementwise subtraction of vector - vector
    template <size_t dim>
    PointVal<dim> operator-(const PointVal<dim> &arr1, const PointVal<dim> &arr2)
    {
        return PointVal<dim>{arr1.P - arr2.P, arr1.Val - arr2.Val};
    }
    /// elementwise multiplication of vector * vector
    template <size_t dim>
    PointVal<dim> operator*(const PointVal<dim> &arr1, const PointVal<dim> &arr2)
    {
        return PointVal<dim>{arr1.P * arr2.P, arr1.Val * arr2.Val};
    }
    template <size_t dim>
    PointVal<dim> operator*(const PointVal<dim>& p, double val)
    {
        return {p.P * val, p.Val * val};
    }
    /// elementwise division of vector / vector
    template <size_t dim>
    PointVal<dim> operator/(const PointVal<dim> &arr1, const PointVal<dim> &arr2)
    {
        return {arr1.P / arr2.P, arr1.Val / arr2.Val};
    }
    /// elementwise division vector / scalar
    template <size_t dim>
    PointVal<dim> operator/(PointVal<dim> arr, double val)
    {
        return PointVal<dim>{arr.P / val, arr.Val / val};
    }

    ///  elementwise sqrt
    template <size_t dim>
    PointVal<dim> sqrt(const PointVal<dim> &p)
    {
        return {sqrt<dim>(p.P), std::sqrt(p.Val)};
    }
    ///  elementwise abs
    template <size_t dim>
    PointVal<dim> abs(const PointVal<dim> &p)
    {
        return {abs<dim>(p.P), std::abs(p.Val)};
    }

    template <size_t dim, typename Stream>
    Stream &operator<<(Stream &o, const PointVal<dim> &r)
    {
        return o << "{ " << r.P << ", " << r.Val << " }";
    }

    /// <summary>
    /// coefficient of variation, mean/variance
    /// </summary>
    /// <typeparam name="point"></typeparam>
    /// <param name="avg"></param>
    /// <param name="disp"></param>
    /// <returns></returns>
    template <typename point>
    std::pair<point, point> VarCoef(const point &avg, const point &disp)
    { // requires sqrt(vector), abs(vector), vector/vector
        auto disp0 = sqrt(disp);
        return std::pair{disp0 / abs(avg), disp0};
    }

   
}

#endif