#ifndef SETOFPOINTS_H
#define SETOFPOINTS_H

#include <array>
#include <tuple>
#include <algorithm>

namespace OptLib
{
    template <size_t count, typename point>
    using RawSetOfPoints = std::array<point, count>;

    template <size_t count, typename point>
    struct SetOfPoints : private RawSetOfPoints<count, point>
    {
        SetOfPoints() = default;

        template <typename T>
        SetOfPoints(T &&p) : RawSetOfPoints<count, point>{std::forward<T>(p)}
        {
        }

        template <typename... Args>
        SetOfPoints(Args... a) : RawSetOfPoints<count, point>{a...}
        {
        }

        point mean() const
        { // requires vector+vector and vector/double
            static_assert(count > 0);

            return 
                 std::accumulate(
                    cbegin()+1, cend(), (*cbegin()),
                    std::plus<point>{}
                ) / (double)count; 
        }

        auto dispersion() const
        { // requires vector+-*vector, vector/double
            static_assert(count > 0);
            point avg{mean()};

            auto functor = [&avg](const point& p)
                {
                    return (p - avg)*(p-avg);
                };

            point result { std::accumulate(
                cbegin()+1, cend(), functor((*cbegin())),
                [&](const point& init, const point& p)
                {
                    return init + functor(p);
                } 
            ) };

            return std::pair<point, point>{avg, result / (double)count};
        }

    public:
        using RawSetOfPoints<count, point>::RawSetOfPoints;
        using RawSetOfPoints<count, point>::operator[];
        using RawSetOfPoints<count, point>::size;
        using RawSetOfPoints<count, point>::begin;
        using RawSetOfPoints<count, point>::end;
        using RawSetOfPoints<count, point>::cbegin;
        using RawSetOfPoints<count, point>::cend;
        using RawSetOfPoints<count, point>::iterator;
        using RawSetOfPoints<count, point>::const_iterator;
        using RawSetOfPoints<count, point>::reverse_iterator;
        using RawSetOfPoints<count, point>::value_type;
    };

} // OptLib

#endif