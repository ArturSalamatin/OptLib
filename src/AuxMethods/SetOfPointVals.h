#ifndef SETOFPOINTVALS_H
#define SETOFPOINTVALS_H

#include "SetOfPoints.h"

namespace OptLib
{
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
}


#endif