#ifndef FUNCTIONWITHMEMORY
#define FUNCTIONWITHMEMORY

#include <atomic>
#include "FuncInterface.h"
#include "FuncParamInterface.h"

namespace OptLib
{
	namespace FunctWithCounter
	{
		/// <summary>
		/// Function Interface f(x) with the ability to count its calls
		/// </summary>
		template <size_t dim>
		class ICounterFunc : public FuncInterface::IFunc<dim>
		{ // direct methods only call the function calculation
			FuncInterface::IFunc<dim>* f;
		public:

			ICounterFunc(FuncInterface::IFunc<dim>* f_pointer) : f{ f_pointer } {}

			double operator () (const Point<dim>& x) const override
			{
				Counter += 1;

				return (*f)(x);
			}

			mutable atomic_size_t Counter {0ull};
		};

		/// <summary>
		/// Function Interface f(x,a) with the ability to count its calls
		/// </summary>
		template<size_t dimX, size_t dimP>
		class ICounterFuncParam : public FuncParamInterface::IFuncParam<dimX, dimP>
		{
			FuncParamInterface::IFuncParam<dimX, dimP>* f;
		public:
			ICounterFuncParam(FuncParamInterface::IFuncParam<dimX, dimP>* f_pointer) : f{ f_pointer } {}

			double operator() (const Point<dimX>& x, const Point<dimP>& a) const override
			{
				/*const_cast<ICounterFuncParam*>(this)->*/Counter += 1;

				return (*f)(x, a);
			}

			mutable atomic_size_t Counter{0ull};
		};
	} // FuncWithCounter
} // OptLib

#endif