#pragma once
#include <functional>
#include <algorithm>
#include <array>

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
	Point<dim> operator + (const Point<dim>& arr1, const Point<dim>& arr2)
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
	Point<dim> operator + (const Point<dim>& arr1, double a)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(),
			result.begin(), 
			SimplexOps::UnaryOps::plus<double>{a });
		return result;  
	}
#pragma endregion

#pragma region SUBTRACT
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(), 
			SimplexOps::BinaryOps::minus<double>{});
		return result;  
	}
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, double a)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), 
			result.begin(), 
			SimplexOps::UnaryOps::minus<double>{a });
		return result;
	}
#pragma endregion

#pragma region MULTIPLY
	template<size_t dim>
	Point<dim> operator* (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(),
			SimplexOps::BinaryOps::multiplies<>{});
		return result;
	}
	template<size_t dim>
	double operator* (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), result.begin(), 
			SimplexOps::UnaryOps:multiplies<double>{consta });

		return result;
	}
#pragma endregion

#pragma region DIVIDE
	template<size_t dim>
	Point<dim> operator/ (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(), 
			SimplexOps::BinaryOps::divides<double>{ });
		return result;
	}
#pragma endregion

#pragma region MISC METHODS
	template<size_t dim>
	double abs(const Point<dim>& arr1)
	{
		Point<dim> result;
		double res = 0;
		std::transform(arr1.begin(), arr1.end(), arr1.begin(), result.begin(), std::multiplies<>{});
		for (auto& el : result)
			res += el;
		return sqrt(res);
	}
	
	template<size_t dim>
	Point<dim> sqrt (const Point<dim>& arr1)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(),
			SimplexOps::UnaryOps::sqrt());
		return result;
	}
#pragma endregion

}

