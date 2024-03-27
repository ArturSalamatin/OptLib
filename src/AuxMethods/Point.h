#ifndef POINT_H
#define POINT_H

#include <iostream>

namespace OptLib
{
	/// @brief Container for scalar function arguments. Static,
	/// compile-time allocation is assumed.
	/// @tparam dim Dimensionality of space
	template <size_t dim>
	using RawPoint = std::array<double, dim>;

	template <size_t dim>
	struct Point : private RawPoint<dim>
	{
		Point() = default;

		template<typename T>
		Point(T&& p) :
			RawPoint<dim>{std::forward<T>(p)}
		{}

		template<typename... Args>
		Point(Args... a) :
			RawPoint<dim>{a...}
		{}

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

	 public:
		using RawPoint<dim>::RawPoint;
		using RawPoint<dim>::operator[];
		using RawPoint<dim>::size;
		using RawPoint<dim>::begin;
		using RawPoint<dim>::end;
		using RawPoint<dim>::iterator;
		using RawPoint<dim>::reverse_iterator;
		using RawPoint<dim>::value_type; 
	};
	
	template<size_t dim, typename Stream>
	Stream& operator<<(Stream& o, const Point<dim>& p)
	{
		static_assert(dim > 0);
		o << "{" << p[0];
		for(size_t i = 1; i < dim; ++i)
		{
			o << ", " << p[i];
		}
		o << "}";
		return o;
	}
} // OptLib

#endif