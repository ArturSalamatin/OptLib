#ifndef STATEINTERFACE_H
#define STATEINTERFACE_H

#include "../Points/SetOfPoints/PointVal/Point/Point.h"
#include "../Points/SetOfPoints/PointVal/PointVal.h"
#include "../Points/SetOfPoints/SetOfPoints.h"
#include "../Points/Definitions.h"

namespace OptLib
{
	namespace StateInterface
	{
		/// @brief Defines abstract basic functions, which are common for every type of state
		/// @tparam dim Dimensionality of space of function arguments
		template<size_t dim>
		class IState
		{
		protected:
			// best-fit value
			PointVal<dim> ItsGuess;
		public:
			// concrete implementation depends on the order of optimization method
			virtual bool IsConverged(double abs_tol, double rel_tol) const = 0;
			const auto& Guess() const { return ItsGuess; };
			const auto& Point() const { return Guess().P; };
			const auto& Value() const { return Guess().Val; };
		};

		/// @brief State for methods of optimization in dim-dimensional space based on simplexes
		/// @tparam simplex Type for the set of points describing the best-fit region
		/// @tparam dim Dimensionality of space of function arguments
		template<size_t dim, typename simplex>
		class IStateSimplex : public IState<dim>
		{
		public: // overriden from predecessor
			bool IsConverged(double abs_tol, double rel_tol) const override
			{// is average and relative tolerance met?
				auto [avg, disp] = GuessDomain().dispersion();
				auto [var, std] = var_coef<PointVal<dim>>(avg, disp) ;

				for (size_t i = 0; i < dim; ++i)
				{
					bool f = ((std[i]) < abs_tol) || (var[i] < rel_tol);
					if (!f) return false;
				}
				return (std.Val < abs_tol) || (var.Val < rel_tol);
			}
		protected:
			simplex ItsGuessDomain; // the field is unique for direct optimization methods
			auto FuncVals(const Simplex<dim>& State, const FuncInterface::IFunc<dim>* f) 
			{
				return (*f)(State);
			}

			void UpdateDomain(Simplex<dim>&& State, const OptLib::Point<dim+1>& funcVals)
			{
				SetDomain(
					simplex{ 
						simplex::make_field(
							std::move(State), 
							funcVals
						) 
					}
				);
			}
		public:
			IStateSimplex() {}

			IStateSimplex(Simplex<dim>&& State, const FuncInterface::IFunc<dim>* f)
			{
				UpdateDomain(std::move(State), f);
			}

			const simplex& GuessDomain() const { return ItsGuessDomain; } // unique for direct optimization methods
			
			void UpdateDomain(Simplex<dim>&& State, const FuncInterface::IFunc<dim>*  f)
			{
				UpdateDomain(std::move(State), FuncVals(State, f));
			}
			virtual void SetDomain(SimplexVal<dim>&& newDomain)
			{
				ItsGuessDomain = simplex{ std::move(newDomain) };

				ItsGuess = GuessDomain().mean();
			}
		};
	} // StateInterface
} // OptLib

#endif