#pragma once
#include <functional>
#include <algorithm>
#include <array>
#include <cmath>

#include "Point.h"
#include "SimplexOps.h"

namespace OptLib
{
#pragma region ADD
	/// @brief elementwise addition of vector + vector
	/// @tparam dim dimensionality of arguments space
	/// @param arr1 lhs argument
	/// @param arr2 rhs argument
	/// @return 
	template<size_t dim>
	auto operator + (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(), 
			arr2.begin(), 
			result.begin(), 
			SimplexOps::BinaryOps::plus<double>{});
		return result;  
	}
	template<size_t dim>
	auto operator + (const Point<dim>& arr1, double a)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(),
			result.begin(), 
			SimplexOps::UnaryOps::plus<double>{a });
		return result;  
	}
	template<size_t dim>
	auto& operator += (Point<dim>& p, double a)
	{
		std::transform(p.begin(), p.end(), p.begin(), SimplexOps::UnaryOps::plus<double>{a});
		return p;
	}
#pragma endregion

#pragma region SUBTRACT
	template<size_t dim>
	auto operator - (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(), 
			SimplexOps::BinaryOps::minus<double>{});
		return result;  
	}
	template<size_t dim>
	auto operator - (const Point<dim>& arr1, double a)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), 
			result.begin(), 
			SimplexOps::UnaryOps::minus<double>{a });
		return result;
	}
	template<size_t dim>
	auto& operator -= (Point<dim>& p, double a)
	{
		std::transform(p.begin(), p.end(), p.begin(), SimplexOps::UnaryOps::minus<double>{a});
		return p;
	}
#pragma endregion

#pragma region MULTIPLY
	template<size_t dim>
	auto operator* (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(),
			SimplexOps::BinaryOps::multiplies<>{});
		return result;
	}
	template<size_t dim>
	auto operator* (const Point<dim>& p, double a)
	{
		Point<dim> result;
		std::transform(
			p.begin(), p.end(), result.begin(), 
			SimplexOps::UnaryOps::multiplies<double>{ a }
		);
		return result;
	}
	template<size_t dim>
	auto& operator *= (Point<dim>& p, double a)
	{
		std::transform(
			p.begin(), p.end(), p.begin(), 
			SimplexOps::UnaryOps::multiplies<double>{a}
		);
		return p;
	}
#pragma endregion

#pragma region DIVIDE
	template<size_t dim>
	auto operator/ (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(), 
			SimplexOps::BinaryOps::divides<double>{ });
		return result;
	}
	template<size_t dim>
	auto& operator /= (Point<dim>& p, double a)
	{
		std::transform(
			p.begin(), p.end(), p.begin(), 
			SimplexOps::UnaryOps::multiplies<double>{1.0/a}
		);
		return p;
	}
#pragma endregion

#pragma region MISC METHODS
	template<size_t dim>
	auto abs(const Point<dim>& arr1)
	{
		Point<dim> result;
		double res{0.0};
		std::transform(arr1.begin(), arr1.end(), arr1.begin(), result.begin(), std::multiplies<>{});
		for (const auto& el : result)
			res += el;
		return std::sqrt(res);
	}
	
	template<size_t dim>
	auto sqrt (const Point<dim>& arr1)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), result.begin(), 
			SimplexOps::UnaryOps::sqrt());
		return result;
	}
#pragma endregion

}

