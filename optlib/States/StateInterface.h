#ifndef STATEINTERFACE_H
#define STATEINTERFACE_H

#include "../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../Points/SetOfPoints/PointVals/PointVal.h"
#include "../Points/SetOfPoints/SetOfPoints.h"
#include "../Points/Definitions.h"

#include "../Functions/Interface/FuncInterface.h"

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
			PointVal<dim> ItsGuess{};
		public:

			constexpr static size_t arg_count = dim;


			IState() = delete;

			template<typename T>
			IState(T&& point_val) noexcept : 
				ItsGuess{std::forward<T>(point_val)}
			{}

			IState(const IState&) noexcept = default;

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
			
			using func_type = FuncInterface::IFunc<dim>;

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
		public:
			IStateSimplex() = delete;

			IStateSimplex(Simplex<dim>&& State, const FuncInterface::IFunc<dim>* f) : 
				IStateSimplex{std::move(State), FuncVals(State, f)}
			{ }

			IStateSimplex(Simplex<dim>&& State, const OptLib::Point<dim+1>& funcVals) :
				IStateSimplex{assign_values<typename simplex::point_type>(State, funcVals)}
			{ }
			
			IStateSimplex(SimplexVal<dim>&& State) :
				IState{State.mean()},
				ItsGuessDomain{State}
			{ }

			IStateSimplex(const Simplex<dim>& State, const FuncInterface::IFunc<dim>* f) : 
				IStateSimplex{State, FuncVals(State, f)}
			{ }

			IStateSimplex(const Simplex<dim>& State, const OptLib::Point<dim+1>& funcVals) :
				IStateSimplex{assign_values<typename simplex::point_type>(State, funcVals)}
			{ }
			
			const simplex& GuessDomain() const { return ItsGuessDomain; } // unique for direct optimization methods
			
			virtual void SetDomain(SimplexVal<dim>&& newDomain)
			{
				ItsGuessDomain = simplex{ std::move(newDomain) };
				ItsGuess = GuessDomain().mean();
			}
		};
	} // StateInterface
} // OptLib

#endif