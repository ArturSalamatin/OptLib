#ifndef FUNCPARAMINTERFACE_H
#define FUNCPARAMINTERFACE_H

#include <array>
#include "../../Points/SetOfPoints/PointVal/Point/Point.h"
#include "../../Points/SetOfPoints/SetOfPoints.h"
#include "FuncInterface.h"

namespace OptLib
{
	namespace FuncParamInterface
	{
		/// <summary>
		/// Function interface that takes array(dimP) of parameters and array(dimX) of arguments
		/// </summary>
		template <size_t dimX, size_t dimP>
		class IFuncParam
		{
		public:
			virtual double operator()(const Point<dimX> &x, const Point<dimP> &a) const = 0;

			template <size_t count>
			Point<count> operator()(const SetOfPoints<count, Point<dimX>> &x, const Point<dimP> &a) const
			{
				std::array<Point<count>::value_type, count> out;
				for (size_t i = 0; i < count; ++i)
					out[i] = (*this))(x[i], a);
				return out;
			}
		};

		template <size_t dimX, size_t dimP>
		class IFuncParamWithGrad : public IFuncParam<dimX, dimP>
		{
		public:
			virtual Grad<dimX> GradP(const Point<dimX> &x, const Point<dimP> &a) const = 0;
		};

		template <size_t dimX, size_t dimP>
		class FuncWithParams : public FuncInterface::IFunc<dimX>
		{
		protected:
			FuncParamInterface::IFuncParam<dimX, dimP> *f;
			Point<dimP> ParamVals;

		public:
			FuncWithParams(Point<dimP> &&pVals, FuncParamInterface::IFuncParam<dimX, dimP> *f_pointer) : f{f_pointer}, ParamVals{std::move(pVals)} {}

			double operator()(const Point<dimX> &x) const override
			{
				return f->operator()(x, ParamVals);
			}
		};

	} // FuncParamInterface
} // OptLib

#endif