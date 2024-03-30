#ifndef POINTOPERATORS_H
#define POINTOPERATORS_H

#include <numeric>

#include "Point.h"
#include "PointOperatorsSerial.h"

namespace OptLib
{
	template<size_t dim, typename Stream>
	auto& operator<<(Stream& o, const Point<dim>& p)
	{
		static_assert(dim > 0);
		o << "{" << p[0];
		if constexpr (dim >1)
		{
		for(size_t i = 1; i < dim; ++i)
		{
			o << ", " << p[i];
		}
		}
		o << "}";
		return o;
	}

	// https://docs.microsoft.com/ru-ru/cpp/parallel/auto-parallelization-and-auto-vectorization?view=msvc-170
	// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=AVX&cats=Store&ig_expand=6846,6917
	// https://habr.com/ru/company/intel/blog/205552/
	// https://chryswoods.com/vector_c++/immintrin.html

	template<size_t dim>
	auto operator + (double a, const Point<dim>& arr1)
	{
		return arr1 + a;
	}
	template<size_t dim>
	auto operator - (double a, const Point<dim>& arr1)
	{
		return a + (-1.0) * arr1;
	}
		
	template<size_t dim>
	auto operator*(double val, const Point<dim>& arr)
	{
		return arr * val;
	}

	template<size_t dim>
	auto operator/ (const Point<dim>& arr1, double a)
	{
		return arr1 * (1.0 / a);
	}
	
	/// scalar product of two vectors
	template <size_t dim>
	auto dot_product(const Point<dim>& x, const Point<dim>& y)
	{
		auto z = x * y;
		return std::accumulate(z.begin(), z.end(), 0.0);
	}
	
    template <size_t dim>
    auto norm(const Point<dim> &p)
    {
        return std::sqrt(dot_product(p,p));
    }

    /// @brief Distance between two points
    /// @tparam dim Dimensionality of space of function arguments
    /// @param p1 First point
    /// @param p2 Second point
    /// @return Distance between two points
    template <size_t dim>
    auto dist(const Point<dim> &p1, const Point<dim> &p2)
    {
        return norm(p1-p2);
    }

} // OptLib

#endif