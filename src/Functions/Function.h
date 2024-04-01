#ifndef FUNCTION_H
#define FUNCTION_H

#include "../Points/SetOfPoints/PointVal/Point/Point.h"
#include "../Points/SetOfPoints/PointVal/Point/PointOperators.h"
#include "../Points/SetOfPoints/SetOfPoints.h"
#include "Interface/FuncInterface.h"

namespace OptLib
{
	namespace ConcreteFunc
	{
		/// <summary>
		/// Templated paraboloid in dim-D space with gradient and hessian
		/// </summary>
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

		/// <summary>
		/// Paraboloid in 2D space, without hessian
		/// </summary>
		using Paraboloid2D = Paraboloid<2>;

		/// <summary>
		/// Parabola in 1D without hessian. mostly a test function...
		/// </summary>
		class Function : public FuncInterface::IFuncWithGrad<1>
		{
		public:
			Function()
			{
#ifdef DEBUG_LIB
				std::cout << "Parabola  x^2  has been instantiated.\n";
#endif // DEBUG_LIB
			}

		public:
			double operator()(const Point<1> &x) const override
			{
				return x[0] * x[0];
			}

			auto grad(const Point<1> &x) const -> Grad<1> override
			{
				return Grad<1>{2 * x[0]};
			}
		};

		/// <summary>
		/// Adding a hessian to a parabola
		/// </summary>
		class FunctionWithHess : public Function, public FuncInterface::IHess<1>
		{
		public:
			virtual auto hess(const Point<1> &x) const -> Hess<1> override
			{
				return Hess<1>{2.0};
			}
		};

		class Function2DWithHessNoGrad : public FuncInterface::IFunc<2>, public FuncInterface::IHess<2>
		{
		public:
			Function2DWithHessNoGrad()
			{
#ifdef DEBUG_LIB
				std::cout << "Parabola  x^2 + y^2  has been instantiated. No gradient is defined.\n";
#endif // DEBUG_LIB
			}
			double operator()(const Point<2> &x) const override
			{
				return x[0] * x[0] + x[1] * x[1];
			}
			auto hess(const Point<2> &x) const -> Hess<2> override
			{
				return Hess<2>{
					Point<2>{2.0, 0.0},
					Point<2>{0.0, 2.0}};
			}
		};

		template <size_t dim>
		class FuncAlongGradDirection : public FuncInterface::IFuncWithGrad<1>
		{
		public:
			FuncAlongGradDirection(
				const FuncInterface::IFuncWithGrad<dim>* const f_pointer, 
				const Point<dim> &x0_) noexcept : 
				x0{x0_}, grad0{f_pointer->grad(x0_)}, f{*f_pointer} 
				{}

			double operator()(const Point<1> &gamma) const override
			{
				return f(x0 - grad0 * gamma[0]);
			}

			Point<1> grad(const Point<1> &gamma) const override
			{
				Point<dim> gr = f.grad(x0 - grad0 * gamma[0]);

				return Point<1>{-dot_product(gr, grad0)};
			}

		protected:
			Point<dim> x0;
			Grad<dim> grad0;

			const FuncInterface::IFuncWithGrad<dim>& f; // function to optimize
		};

		template <size_t dim>
		class Func : public FuncInterface::IFunc<dim>
		{
		public:
			Func()
			{
#ifdef DEBUG_LIB
				std::cout << "Paraboloid  has been instantiated.\n";
#endif // DEBUG_LIB
			}

		public:
			virtual double operator()(const Point<dim> &x) const override
			{
				double res = 0.0;
				for (size_t i = 0; i < dim; ++i)
				{
					res += x[i] * x[i];
				}
				return res;
			}
		};

		class Himmel : public FuncInterface::IFuncWithHess<2>
		{
		public:
			Himmel()
			{
#ifdef DEBUG_LIB
				std::cout << "Himmel funcion  has been created.\n";
				std::cout << "f(3,2) = " << this->operator()(Point<2>{3, 2}) << '\n';
				std::cout << "f(-2.805118,3.131312) = " << this->operator()(Point<2>{-2.805118, 3.131312}) << '\n';
				std::cout << "f(-3.779310,-3.283186) = " << this->operator()(Point<2>{-3.779310, -3.283186}) << '\n';
				std::cout << "f(3.584428,-1.848126) = " << this->operator()(Point<2>{3.584428, -1.848126}) << '\n';
#endif // DEBUG_LIB
			}
			double operator()(const Point<2> &x) const override
			{
				return std::pow(x[0] * x[0] + x[1] - 11.0, 2.0) + std::pow(x[0] + x[1] * x[1] - 7.0, 2.0);
			}

			Point<2> grad(const Point<2> &x) const override
			{
				return Point<2>{
					4.0 * x[0] * x[0] * x[0] + 
					4.0 * x[0] * x[1] - 
					42.0 * x[0] + 
					2.0 * x[1] * x[1] - 14.0, 

					2.0 * x[0] * x[0] - 22.0 + 
					4.0 * x[0] * x[1] + 
					4.0 * x[1] * x[1] * x[1] - 
					26.0 * x[1]};
			}

			Hess<2> hess(const Point<2> &x) const override
			{
				return Hess<2>{Grad<2>{12.0 * x[0] * x[0] + 4 * x[1] - 42.0, 4.0 * x[0] + 4.0 * x[1]},
								Grad<2>{4.0 * x[0] + 4.0 * x[1], 4.0 * x[0] + 12.0 * x[1] * x[1] - 26.0}};
			}
		};

		class Rozenbrok : public FuncInterface::IFuncWithHess<2>
		{
		public:
			Rozenbrok()
			{
#ifdef DEBUG_LIB
				std::cout << "Rozenbrok funcion has been instantiated.\n";
				std::cout << "f(1,1) = " << this->operator()(Point<2>{1, 1}) << '\n';
#endif // DEBUG_LIB
			}
			double operator()(const Point<2> &x) const override
			{
				return std::pow((1 - x[0]), 2) + 100 * std::pow(x[1] - x[0] * x[0], 2);
			}

			Grad<2> grad(const Point<2> &x) const override
			{
				return Grad<2>{-2 * x[0] * (1 - x[0] + 200 * (x[1] - x[0] * x[0])), 200 * (x[1] - x[0] * x[0])};
			}

			Hess<2> hess(const Point<2> &x) const override
			{
				return Hess<2>{Grad<2>{-2.0 * (1.0 - x[0] + 200.0 * (x[1] - x[0] * x[0])) - 2.0 * x[0] * (-1.0 - 400.0 * x[0]),
								 -400.0 * x[0]},
								Grad<2>{-400.0 * x[0], 200.0}};
			}
		};

	} // ConcreteFuncs
} // OptLib

#endif