#ifndef FUNCALONGGRADDIRECTION_H
#define FUNCALONGGRADDIRECTION_H

#include "../Points/SetOfPoints/PointVals/Point/PointOperators.h"
#include "Interface/FuncInterface.h"

namespace OptLib
{
    namespace ConcreteFunc
    {
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

    }
}


#endif 