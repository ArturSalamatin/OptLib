#ifndef PARABOLOID_H
#define PARABOLOID_H

#include "Interface/FuncInterface.h"
#include "../Points/SetOfPoints/PointVals/Point/PointOperators.h"
#include "../Points/SetOfPointVals.h"
#include "../Points/SetOfPoints/SetOfPointOperators.h"

namespace OptLib
{
    namespace ConcreteFunc
    {
        /**
		 * @brief Templated paraboloid in dim-D space with gradient and hessian
		 * 
		 */
		template <size_t dim>
		class Paraboloid : public FuncInterface::IFuncWithHess<dim>
		{
		protected:
			Hess<dim> hessian, coef_matrix;

		public:
			Paraboloid(const Hess<dim>& coefs) : hessian{coefs}, coef_matrix{coefs}
			{
				// transform coefficientts to hessian symmetric matrix
				// make the hessian matrix symmetric
				for (size_t i = 0; i < dim; ++i)
				{
					hessian[i][i] *= 2;
					for (size_t j = i + 1; j < dim; ++j)
					{
						double temp = (hessian[i][j] + hessian[j][i]);
						hessian[i][j] = temp;
						hessian[j][i] = temp;
					}
				}
				// make the coefficient matrix symmetric
				for (size_t i = 0; i < dim; ++i)
					for (size_t j = i + 1; j < dim; ++j)
					{
						double temp = (coef_matrix[i][j] + coef_matrix[j][i]) / 2.0;
						coef_matrix[i][j] = temp;
						coef_matrix[j][i] = temp;
					}
#ifdef DEBUG_LIB
				std::cout << "Paraboloid in " << dim << "D space with Hessian "
						  << hessian << " has been instantiated\n";
				std::cout << "Its coefficient matrix A for xAx is " << CoefMatrix() << '\n';
#endif // DEBUG_LIB
			}

			auto operator()(const Point<dim> &x) const -> typename Point<dim>::value_type override
			{
				Point<dim>::value_type result{0.0};
				for (size_t i = 0; i < dim; ++i)
				{
					result += hessian[i][i] / 2.0 * x[i] * x[i];
					for (size_t j = i + 1; j < dim; ++j)
						result += hessian[i][j] * x[i] * x[j];
				}
				return result;
			}

			auto grad(const Point<dim> &x) const -> Grad<dim> override
			{
				Grad<dim> result{};
				for (size_t i = 0; i < dim; ++i)
					result[i] = 2 * dot_product(x, CoefMatrixRow(i));
				return result;
			}

			auto hess(const Point<dim> &x) const -> Hess<dim> override
			{
				return hessian;
			}

		protected:
			const SetOfPoints<dim, Point<dim>> &CoefMatrix() const
			{
				return coef_matrix;
			}
			const Point<dim> &CoefMatrixRow(size_t i) const
			{
				return CoefMatrix()[i];
			}
		};

        
		/**
		 * @brief Paraboloid in 2D space, without hessian
		 * 
		 */
		using Paraboloid2D = Paraboloid<2>;
    }
}

#endif