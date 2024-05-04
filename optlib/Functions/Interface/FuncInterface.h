#ifndef FUNCTERFACE_H
#define FUNCTERFACE_H

#include <array>
#include "../../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../../Points/SetOfPoints/PointVals/PointVal.h"
#include "../../Points/SetOfPoints/SetOfPoints.h"

namespace OptLib
{
	template <size_t dim>
	using Grad = Point<dim>;

	template <size_t dim>
	using Hess = SetOfPoints<dim, Grad<dim>>;

	namespace FuncInterface
	{
		template <size_t dim>
		class IFunc
		{ // direct methods only call the function calculation
		public:
			virtual double operator()(const Point<dim> &) const = 0;

			template <size_t count>
			auto operator()(const SetOfPoints<count, Point<dim>> &x) const
			{
				Point<count> out;
				for (size_t i = 0; i < count; ++i)
					out[i] = (*this)(x[i]);
				return out;
			}
		};

		template <size_t dim>
		static auto CreateFromPoint(Point<dim> &&p, const IFunc<dim> *f)
		{
			PointVal<dim> out;
			out.P = std::move(p);
			out.Val = (*f)(out.P);
			return out;
		}

		template <size_t dim>
		class IGrad
		{
		public:
			virtual Grad<dim> grad(const Point<dim> &) const = 0;

			template <size_t count>
			auto grad(const SetOfPoints<count, Point<dim>> &x) const
			{
				SetOfPoints<count, Grad<dim>> out;
				for (size_t i = 0; i < count; ++i)
					out[i] = (*this).grad(x[i]);
				return out;
			}
		};

		template <size_t dim>
		class IHess
		{
		public:
			// each Point<dim> is a row of the Hessian matrix
			virtual Hess<dim> hess(const Point<dim> &x) const = 0;
		};

		template <size_t dim>
		class IFuncWithGrad : public IFunc<dim>, public IGrad<dim>
		{
		}; // 1st order optimization methods require the function itself and the gradient

		template <size_t dim>
		class IFuncWithHess : public IFuncWithGrad<dim>, public IHess<dim>
		{
		}; // 2nd order methods --- function, gradient, and hessian

	} // FuncInterface
} // OptLib

#endif