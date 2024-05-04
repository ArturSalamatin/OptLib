#ifndef HIMMEL_H
#define HIMMEL_H

#include <cmath>
#include "Interface/FuncInterface.h"

namespace OptLib
{
    namespace ConcreteFunc
    {
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
    }
}

#endif