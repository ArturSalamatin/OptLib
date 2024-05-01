#ifndef ROZENBROCK_H
#define ROZENBROCK_H

#include <cmath>
#include "Interface/FuncInterface.h"

namespace OptLib
{
    namespace ConcreteFunc
    {
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

    } // ConcreteFunc
} // OptLib


#endif