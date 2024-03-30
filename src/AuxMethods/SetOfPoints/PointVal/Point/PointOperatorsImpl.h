#ifndef POINTOPERATORSIMPL_H
#define POINTOPERATORSIMPL_H

#include <functional>

namespace OptLib
{
	namespace PointOps
	{
		namespace UnaryOps
		{
			/// @brief Addition of Point-element and a fixed scalar
			/// @tparam Scalar Value to be added to every element of Point-container
			template <class Scalar>
			struct plus
			{
				plus(Scalar value) : 
					scalar{value} 
				{}

				constexpr Scalar operator()(const Scalar &lhs) const
				{
					return lhs + scalar;
				}

			protected:
				Scalar scalar;
			};

			/// @brief Subtraction of a fixed scalar from Point-element 
			/// @tparam Scalar Value to be subtracted from every element of Point-container
			template <class Scalar>
			struct minus
			{
				minus(Scalar value) : 
					scalar{value} 
				{}

				constexpr Scalar operator()(const Scalar &lhs) const
				{
					return lhs - scalar;
				}

			protected:
				Scalar scalar;
			};

			/// @brief Multiplication of Point-element and a fixed scalar
			/// @tparam Scalar Value to be multiplied with every element of Point-container
			template <class Scalar>
			struct multiplies
			{
				multiplies(Scalar value) : 
					scalar{value} 
				{}

				constexpr Scalar operator()(const Scalar &lhs) const
				{
					return lhs * scalar;
				}

			protected:
				Scalar scalar;
			};

			struct sqrt
			{
				template <class T>
				constexpr T operator()(const T &lhs) const
				{
					return std::sqrt(lhs);
				}
			};
			
			struct abs
			{
				template <class T>
				constexpr T operator()(const T &lhs) const
				{
					return std::abs(lhs);
				}
			};
		}

		namespace BinaryOps
		{
			template <class T = void>
			using plus = std::plus<T>;

			template <class T = void>
			using minus = std::minus<T>;

			template <class T = void>
			using multiplies = std::multiplies<T>;

			template <class T = void>
			using divides = std::divides<T>;
		} // BinaryOps
	} // SimplexOps
} // OptLib

#endif