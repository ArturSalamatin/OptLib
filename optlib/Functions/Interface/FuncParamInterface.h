#ifndef FUNCPARAMINTERFACE_H
#define FUNCPARAMINTERFACE_H

#include <array>
#include "../../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../../Points/SetOfPoints/SetOfPoints.h"
#include "FuncInterface.h"

namespace OptLib
{
	namespace FuncParamInterface
	{
		/// @brief Function interface f(X | P) that takes array(dimP) of parameters and array(dimX) of arguments
		/// @tparam dimX number of arguments
		/// @tparam dimP number of parameters
		template <size_t dimX, size_t dimP>
		class IFuncParam
		{
		public:
			virtual double operator()(const Point<dimX> &x, const Point<dimP> &a) const = 0;

			template<size_t count>
			auto operator()(const SetOfPoints<count, Point<dimX>> &x, const Point<dimP> &a) const 
			{
				Point<count> out{};
				for (size_t i = 0; i < count; ++i)
					out[i] = (*this)(x[i], a);
				return out;
			}
		};

		template <size_t dimX, size_t dimP>
		class IFuncParamGrad
		{
		public:
			virtual Grad<dimX> GradP(const Point<dimX> &x, const Point<dimP> &a) const = 0;
		};

		template <size_t dimX, size_t dimP>
		class FuncParams : public FuncInterface::IFunc<dimX>
		{
		protected:
			const FuncParamInterface::IFuncParam<dimX, dimP>& f;
			Point<dimP> ParamVals;

		public:
		template<typename T>
			FuncParams(T&& pVals, FuncParamInterface::IFuncParam<dimX, dimP> *f_pointer) : f{*f_pointer}, ParamVals{std::forward<T>(pVals)} {}

			double operator()(const Point<dimX> &x) const override
			{
				return f(x, ParamVals);
			}
		};

		template <size_t dimX, size_t dimP>
		class IFuncParamWithGrad : public IFuncParam<dimX, dimP>, public IFuncParamGrad<dimX, dimP>
		{
		};
	} // FuncParamInterface
} // OptLib

#endif