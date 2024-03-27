#ifndef SETOFPOINTS_H
#define SETOFPOINTS_H

#include <tuple>
#include "Point.h"

namespace OptLib
{
    template <size_t count, typename point>
    using RawSetOfPoints = std::array<point, count>;

    template <size_t count, typename point>
    struct SetOfPoints : private RawSetOfPoints<count, point>
    {
        SetOfPoints() = default;

        template <typename T>
        SetOfPoints(T &&p) : RawSetOfPoints<dim>{std::forward<T>(p)}
        {
        }

        template <typename... Args>
        SetOfPoints(Args... a) : RawSetOfPoints<dim>{a...}
        {
        }

        /* Point(std::initializer_list<double> lp) :
            RawPoint<dim>{lp}
        {} */

        /* template<typename T>
        Point(T p) :
            RawPoint<dim>{p}
        {} */

        /* Point(const RawPoint<dim>& p) :
            RawPoint<dim>{p}
        {} */

        point Mean() const
        { // requires vector+vector and vector/double
            return std::accumulate(begin(), end(), std::plus<>{})/(double)count;
        }

        std::pair<point, point> Dispersion() const
        { // requires vector+-*vector, vector/double
            point avg{Mean()};

            point result = (Points()[0] - avg) * (Points()[0] - avg);

            for (size_t i = 1; i < count; ++i)
                result = result + (Points()[i] - avg) * (Points()[i] - avg);

            return {avg, result / (count + 0.0)};
        }

    public:
        using RawSetOfPoints<count, point>::RawPoint;
        using RawSetOfPoints<count, point>::operator[];
        using RawSetOfPoints<count, point>::size;
        using RawSetOfPoints<count, point>::begin;
        using RawSetOfPoints<count, point>::end;
        using RawSetOfPoints<count, point>::iterator;
        using RawSetOfPoints<count, point>::reverse_iterator;
        using RawSetOfPoints<count, point>::value_type;
    };

    /// <summary>
    /// A matrix*vector multiplication
    /// </summary>
    /// <param name="A"></param>
    /// <param name="B"></param>
    /// <returns></returns>
    template <size_t count, size_t dim>
    Point<count> operator*(const SetOfPoints<count, Point<dim>> &A, const Point<dim> &B)
    {
        Point<count> out;
        for (size_t i = 0; i < dim; ++i)
            out[i] = dot_product(A[i], B);
        return out;
    }

    template <size_t count, typename point, typename Stream>
    Stream &operator<<(
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


    template <size_t count, typename point, typename Stream>
    Stream &operator<<(Stream &o, const RawSetOfPoints<count, point> &output)
    {
        o << "{ " << output[0];
        for (size_t i = 1; i < count; ++i)
            o << "; " << output[i];
        o << " }";
        return o;
    }

    /// <summary>
    /// Set of points with associated value. The calss makes PointVal from Point and Val
    /// </summary>
    /// <typeparam name="point"></typeparam>
    /// <typeparam name="pointval"></typeparam>
    template <size_t count, typename pointval>
    class SetOfPointVal : public SetOfPoints<count, pointval>
    {
    public:
        /// <summary>
        /// assembles PointVal from Point and Val
        /// </summary>
        /// <param name="_s"></param>
        /// <param name="FuncVals"></param>
        /// <returns></returns>
        template<typename point>
        static SetOfPoints<count, pointval> make_field(
            SetOfPoints<count, point> &&_s, 
            const std::array<double, count> &FuncVals)
        {
            SetOfPoints<count, pointval> P;
            for (size_t i = 0; i < count; ++i)
                P[i] = pointval{std::move(_s[i]), FuncVals[i]};
            return P;
        }

    public:
        SetOfPointVal() = default;
        SetOfPointVal(SetOfPoints<count, pointval> &&_s) : RawSetOfPoints<count, pointval>{std::move(_s)} {}
        template<typename point>
        SetOfPointVal(SetOfPoints<count, point> &&_s, const std::array<double, count> &funcVals) : // transforms points to points with vals
                                                                                                   SetOfPointVal<count, point, pointval>{make_field(std::move(_s), funcVals)}
        {
        }

        template<typename point>
        SetOfPoints<count, point> PointsNoVal() const
        {
            SetOfPoints<count, point> out{};
            for (size_t i = 0; i < count; i++)
                out[i] = (*this)[i].P;
            return out;
        }
    };

    /// <summary>
    /// A set of points of type {point with Val} with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef. The points are sorted according to Val-field.
    /// </summary>
    /// <typeparam name="point"></typeparam>
    template <size_t count, typename pointval>
    class SetOfPointValsSort : public SetOfPointVal<count, pointval>
    {
    private:
        void Sort() { std::sort(ItsSetOfPoints.begin(), ItsSetOfPoints.end()); }

    public:
        SetOfPointValsSort() = default;
        SetOfPointValsSort(SetOfPoints<count, pointval> &&_s) : SetOfPointVal<count, point, pointval>{std::move(_s)} { this->Sort(); }
        template<typename point>
        SetOfPointValsSort(SetOfPoints<count, point> &&_s, const std::array<double, count> &funcVals) : // transforms points to points with vals
                                                                                                        SetOfPointVal<count, point, pointval>{std::move(_s), funcVals}
        {
            this->Sort();
        }
    };

    template <size_t dim>
    using SimplexValNoSort = SetOfPointVal<dim + 1, Point<dim>, PointVal<dim>>;

    using Segment = SimplexValNoSort<1>;

    template <size_t dim>
    using SimplexValSort = SetOfPointValsSort<dim + 1, Point<dim>, PointVal<dim>>;

    template <size_t dim>
    using Grad = Point<dim>;

    template <size_t dim>
    using Hess = SetOfPoints<dim, Point<dim>>;
} // OptLib

#endif