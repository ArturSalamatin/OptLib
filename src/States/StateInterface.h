#ifndef STATEINTERFACE_H
#define STATEINTERFACE_H

#include "../Points/SetOfPoints/PointVal/Point/Point.h"
#include "../Points/SetOfPoints/PointVal/PointVal.h"
#include "../Points/SetOfPoints/SetOfPoints.h"

namespace OptLib
{
	namespace StateInterface
	{
		/// <summary>
		/// defines abstract basic functions, which are common for every type of state
		/// </summary>
		template<size_t dim>
		class IState
		{
		protected:
			PointVal<dim> ItsGuess;
		public:
			// concrete implementation depends on the order of optimization method
			virtual bool IsConverged(double abs_tol, double rel_tol) const  = 0;
			const PointVal<dim>& Guess() const { return ItsGuess; };
		};

		/// <summary>
		/// State for methods of optimization in dim-dimensional space based on simplexes
		/// </summary>
		template<size_t dim, typename simplex>
		class IStateSimplex : public IState<dim>
		{
		public: // overriden from predecessor
			bool IsConverged(double abs_tol, double rel_tol) const override
			{// is average and relative tolerance met?
				auto [avg, disp] = GuessDomain().Dispersion();
				auto [var,std] = VarCoef<PointVal<dim>>(avg, disp) ;

				for (size_t i = 0; i < dim; ++i)
				{
					bool f = (((std[i]) < abs_tol) || (var[i] < rel_tol)) && (((std.Val) < abs_tol) || (var.Val < rel_tol));
					if (!f) return false;
				}
				return true;
			}
		protected:
			simplex ItsGuessDomain; // the field is unique for direct optimization methods
			auto FuncVals(const SetOfPoints<dim + 1, Point<dim>>& State, const FuncInterface::IFunc<dim>* f) 
			{
				return (*f)(State);
			}
			void UpdateDomain(SetOfPoints<dim + 1, Point<dim>>&& State, Point<dim + 1>&& funcVals)
			{
				SetDomain(
					simplex{ 
						simplex::make_field(
							std::move(State), 
							std::move(funcVals)
						) 
					}
				);
			}
		public:
			IStateSimplex() {}
			/*IStateSimplex(const SetOfPoints<dim + 1, Point<dim>>& State, FuncInterface::IFunc<dim>* f)
			{
				auto s{ State };
				UpdateDomain(std::move(s), f);
			}*/
			IStateSimplex(SetOfPoints<dim + 1, Point<dim>>&& State, FuncInterface::IFunc<dim>* f)
			{
				UpdateDomain(std::move(State), f);
			}
			const simplex& GuessDomain() const { return ItsGuessDomain; } // unique for direct optimization methods
			
			void UpdateDomain(SetOfPoints<dim + 1, Point<dim>>&& State, const FuncInterface::IFunc<dim>* f)
			{
				UpdateDomain(std::move(State), std::move(FuncVals(State, f)));
			}
			virtual void SetDomain(SetOfPoints<dim + 1, PointVal<dim>>&& newDomain)
			{
				ItsGuessDomain = simplex{ std::move(newDomain) };

				ItsGuess = GuessDomain().Mean();
			}
		};
	} // StateInterface
} // OptLib

#endif