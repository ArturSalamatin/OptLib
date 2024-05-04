#pragma once
#include "Point.h"

namespace OptLib
{
	/// elementwise addition of vector + vector
	template<size_t dim>
	Point<dim> operator+(
		const Point<dim>& arr1, 
		const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);
		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_add_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] + arr2[i];
		}

		//	std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<> {});
		return result;
	}
	/// elementwise addition of vector + value
	Point<1> operator+ (Point<1>& p, double a)
	{
		p[0] += a;
		return p;
	}
	template<size_t dim>
	Point<dim> operator + (
		const Point<dim>& arr1, 
		double a)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(),
			SimplexOps::UnaryOps::plus<double>{ a });
		return result;
	}

	/// elementwise subtraction of vector - vector
	template<size_t dim>
	Point<dim> operator-(
		const Point<dim>& arr1, 
		const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);
		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_sub_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] - arr2[i];
		}

		//	std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<> {});
		return result;
	}

	template<size_t dim>
	Point<dim> operator - (const Point<dim>& arr1, double a)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::minus<double>{consta });
		return result;
	}

	/// elementwise division vector / scalar
	template<size_t dim>
	Point<dim> operator/(
		const Point<dim>& arr, double val)
	{
		Point<dim> result;
		__m256d Val = _mm256_set1_pd(val);
		__m256d x;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);

				x = _mm256_div_pd(x, Val);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr[i] / val;
		}


		//	for (auto& elem : arr)
		//		elem /= val;
		return result;
	}

	/// elementwise division of vector / vector
	template<size_t dim>
	Point<dim> operator/(
		const Point<dim>& arr1, 
		const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_div_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] / arr2[i];
		}

		//		std::transform(arr1.begin(), arr1.end(),
		//			arr2.begin(), result.begin(), [](double x, double y) {return x / y; });
		return result;
	}


	/// elementwise multiplication of vector * vector
	template<size_t dim>
	Point<dim> operator*(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);
		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_mul_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] * arr2[i];
		}

		//	std::transform(arr1.begin(), arr1.end(),
		//		arr2.begin(), result.begin(), [](double x, double y) {return x * y; });

		return result;
	}

	/// elementwise multiplication of vector * scalar
	template<size_t dim>
	Point<dim> operator*(const Point<dim>& arr, double val)
	{
		Point<dim> result;
		__m256d Val = _mm256_set1_pd(val);
		__m256d x;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);

				x = _mm256_mul_pd(x, Val);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = arr[i] * val;
		}
		return result;
	}


	/// elementwise sqrt
	template<size_t dim>
	Point<dim> sqrt(const Point<dim>& arr)
	{
		Point<dim> result;
		__m256d x;

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);
				x = _mm256_sqrt_pd(x);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; i++)
				result[i] = std::sqrt(arr[i]);
		}

		return result;
	}

	/// elementwise abs
	template<size_t dim>
	Point<dim> abs(const Point<dim>& arr)
	{
		Point<dim> result;
		__m256d x;
		static const __m256d signmask = _mm256_set1_pd(-0.0f); // 0x80000000

		constexpr size_t byte_size = 8;
		constexpr size_t rg_size = 256 / byte_size / sizeof(Point<dim>::value_type);
		constexpr size_t itr = dim / rg_size;

		for (size_t i = 0; i < itr; i++)
		{
			x = _mm256_loadu_pd(arr.data() + i * rg_size);
			x = _mm256_andnot_pd(signmask, x);

			_mm256_storeu_pd(result.data() + i * rg_size, x);
		}

		if constexpr (dim % rg_size != 0)
		{
			for (size_t i = itr * rg_size; i < dim; ++i)
				result[i] = std::abs(arr[i]);
		}
		return result;
	}


} // OptLib
