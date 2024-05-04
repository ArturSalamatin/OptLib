#ifndef FUNCTIONPARAM_H
#define FUNCTIONPARAM_H

#include "Interface/FuncParamInterface.h"

namespace OptLib
{
	namespace ConcreteFuncParam
	{
		class LinearFunc : public FuncParamInterface::IFuncParam<1, 1>
		{
		public:
			double operator() (const Point<1>& x, const Point<1>& a) const override
			{
				return x[0] * a[0];
			}
		};

		class LinearFuncWithGrad : public LinearFunc, FuncParamInterface::IFuncParamGrad<1, 1>
		{
		public:
			double operator() (const Point<1>& x, const Point<1>& a) const override
			{
				return x[0] * a[0];
			}
			auto GradP(const Point<1>& x, const Point<1>& a) const -> Grad<1> override
			{
				return Grad<1>{a};
			}
		};
	} // ConcreteFuncParam
} // OptLib

#endif