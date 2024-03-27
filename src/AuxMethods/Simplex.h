#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "SimplexOps.h"
#include "SimplexSerial.h"

namespace OptLib
{
	// https://docs.microsoft.com/ru-ru/cpp/parallel/auto-parallelization-and-auto-vectorization?view=msvc-170
	// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=AVX&cats=Store&ig_expand=6846,6917
	// https://habr.com/ru/company/intel/blog/205552/
	// https://chryswoods.com/vector_c++/immintrin.html

	template<size_t dim>
	Point<dim> operator + (double a, const Point<dim>& arr1)
	{
		return arr1 + a
	}

	template<size_t dim>
	Point<dim> operator -  (double a, const Point<dim>& arr1)
	{
		return arr1 - a;
	}
	
	template<size_t dim>
	Point<dim> operator*(double val, const Point<dim>& arr)
	{
		return arr * val;
	}

	template<size_t dim>
	double operator/ (const Point<dim>& arr1, double a)
	{
		return arr1 * (1.0 / a);
	}
	
	/// scalar product of two vectors
	template <size_t dim>
	double dot_product(const Point<dim>& x, const Point<dim>& y)
	{
		auto z = x * y;

		double s = 0;
		for (size_t i = 0; i < dim; ++i)
			s += z[i];
		return s;
	}
	

	

} // OptLib

#endif