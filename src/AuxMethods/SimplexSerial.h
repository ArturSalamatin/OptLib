#pragma once
#include <functional>
#include <algorithm>
#include <array>

#include"SimplexOps.h"

namespace OptLib
{
	/// elementwise addition of vector + vector
	template<size_t dim>
	Point<dim> operator + (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; // новый массив с тем же кол-вом значений
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<>{});
		return result;  // дз по минусу, произведение на число и скалярное, модуль
	}
	template<size_t dim>
	Point<dim> operator + (const Point<dim>& arr1, double a)
	{
		Point<dim> result; 
		std::transform(arr1.begin(), arr1.end(), result.begin(), 
			SimplexOps::UnaryOps::plus<double>{a });
		return result;  
	}
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result; 
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(), 
			std::minus<>{});
		return result;  
	}
	template<size_t dim>
	Point<dim> operator/ (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;

		for (size_t i = 0; i < dim; ++i)
			result[i] = arr1[i] / arr2[i];
		return result;
	}
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
	Point<dim> sqrt (const Point<dim>& arr1)
	{
		Point<dim> result;
		std::transform(
			arr1.begin(), arr1.end(), arr2.begin(), result.begin(),
			SimplexOps::UnaryOps::sqrt());
		return result;
	}
	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::minus<double>{consta });
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
}

