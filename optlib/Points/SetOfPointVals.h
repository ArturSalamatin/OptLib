#ifndef SETOFPOINTVALS_H
#define SETOFPOINTVALS_H

#include "SetOfPoints/PointVals/Point/Point.h"
#include "SetOfPoints/SetOfPoints.h"

namespace OptLib
{
    /// <summary>
    /// assembles PointVal from Point and Val
    /// </summary>
    /// <param name="_s"></param>
    /// <param name="FuncVals"></param>
    /// <returns></returns>
    template <typename pointval, size_t count, typename T>
    auto assign_values(
        T &&s,
        const Point<count> &FuncVals)
    {
        SetOfPoints<count, pointval> P;
        for (size_t i = 0; i < count; ++i)
            P[i] = pointval{std::forward<decltype(s[0])>(s[i]), FuncVals[i]};
        return P;
    }

    /// <summary>
    /// Set of points with associated value. The calss makes PointVal from Point and Val
    /// </summary>
    /// <typeparam name="point"></typeparam>
    /// <typeparam name="pointval"></typeparam>
    template <size_t count, typename pointval>
    class SetOfPointVals : public SetOfPoints<count, pointval>
    {
    public:
        using point_type = pointval;

        SetOfPointVals() = default;
        template <typename T>
        SetOfPointVals(T &&s) : SetOfPoints<count, pointval>{std::forward<T>(s)} {}
        template <typename T>
        SetOfPointVals(
            T &&s,
            const std::array<double, count> &funcVals) : // transforms points to points with vals
                                                         SetOfPointVals<count, pointval>{assign_values<pointval>(std::forward(s), funcVals)}
        {
        }

        template <typename point>
        auto PointsNoVal() const
        {
            SetOfPoints<count, point> out{};
            for (size_t i = 0; i < count; ++i)
                out[i] = (*this)[i].P;
            return out;
        }
    };

    /// <summary>
    /// A set of points of type {point with Val} with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef. The points are sorted according to Val-field.
    /// </summary>
    /// <typeparam name="point"></typeparam>
    template <size_t count, typename pointval>
    class SetOfPointValsSort : public SetOfPointVals<count, pointval>
    {
    private:
        void Sort() { std::sort(begin(), end()); }

    public:
        SetOfPointValsSort() = default;

        template <typename T>
        SetOfPointValsSort(T &&s) : SetOfPointVals<count, pointval>{std::forward<T>(s)}
        {
            this->Sort();
        }

        template <typename T>
        SetOfPointValsSort(
            T &&s,
            const std::array<double, count> &funcVals) : // transforms points to points with vals
                                                         SetOfPointValsSort<count, pointval>{make_field(std::forward<T>(s), funcVals)}
        {
        }
    };
}

#endif