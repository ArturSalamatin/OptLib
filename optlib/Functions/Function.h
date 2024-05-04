#ifndef FUNCTION_H
#define FUNCTION_H

#include "../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../Points/SetOfPoints/PointVals/Point/PointOperators.h"
#include "../Points/SetOfPoints/SetOfPoints.h"
#include "Interface/FuncInterface.h"

namespace OptLib
{
	namespace ConcreteFunc
	{
		/**
		 * @brief Parabola in 1D without hessian. mostly a test function...
		*/
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

		/**
		 * @brief Adding a hessian to a parabola
		 * 
		 */
		class FunctionWithHess : public Function, public FuncInterface::IHess<1>
		{
		public:
			auto hess(const Point<1> &x) const -> Hess<1> override
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
			double operator()(const Point<dim> &x) const override
			{
				double res = 0.0;
				for (size_t i = 0; i < dim; ++i)
				{
					res += x[i] * x[i];
				}
				return res;
			}
		};
	} // ConcreteFunc
} // OptLib

#endif