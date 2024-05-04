#ifndef OPTIMIZERINTERFACE_H
#define OPTIMIZERINTERFACE_H

#include "../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../Points/SetOfPoints/PointVals/Point/PointOperators.h"

#include "../Points/SetOfPoints/PointVals/PointVal.h"
#include "../Points/SetOfPoints/PointVals/PointValOperators.h"

#include "../Functions/Interface/FuncInterface.h"

#include "../States/StateInterface.h"

namespace OptLib
{
	namespace OptimizerInterface
	{
		template<size_t dim> // nmbr of x-params
		class OptimizerAlgorithm
		{
		public:
			static Point<dim> CurrentGuess(
				const StateInterface::IState<dim>* State) 
				{ 
					return State->Guess(); 
				}; // returns current guess
			static PointVal<dim> CurrentPointAndVal(
				const StateInterface::IState<dim>* State, 
				const FuncInterface::IFunc<dim>* f) 
				// returns the guess and the function value
			{
				Point<dim> p = CurrentGuess(State);
				return {std::move(p), f->operator()(p)};
			}

			static bool IsConverged(
				const StateInterface::IState<dim>* State, 
				double abs_tol, double rel_tol)
			{
				return State->IsConverged(abs_tol, rel_tol);
			}

			template<
				typename algo,
				typename state,
				typename func>
			static PointVal<dim> Proceed(
				state* State, const func* f) 
			{ 
				return algo::Proceed(*State, f); 
			}; // continue to next guess. The state is updated
		};

		// template<size_t dim, typename state>
		// class ISimplexAlgo : public OptimizerAlgorithm<dim>
		// {
		// public:
		// 	static const auto& GuessDomain(const state* State) { return State->GuessDomain(); } // unique for direct methods
		// };

		// /// <summary>
		// /// Direct optimization in N-dim space with simplex points sorting according to f(x)
		// /// </summary>
		// template<size_t dim>
		// using IDirectAlgo = ISimplexAlgo<dim, ConcreteState::StateDirect<dim>>;

		// /// <summary>
		// /// Algorithms for 1D optimization on a segment. Segment [x1; x2], where it is guaranteed that x1 < x2
		// /// </summary>
		// using ISegmentAlgo = ISimplexAlgo<1, ConcreteState::StateSegment>;

		// template<size_t dim>
		// class IGradAlgo : public OptimizerAlgorithm<dim>
		// {

		// };

		// template<size_t dim>
		// class IHessAlgo : public OptimizerAlgorithm<dim>
		// {

		// };

		// template<size_t dim>
		// class IStochasticAlgo : public OptimizerAlgorithm<dim>
		// {

		// };
		
		// template<size_t dim>
		// class IGAAlgo : public OptimizerAlgorithm<dim>
		// {

		// };
	} // OptimizerInterface
} // OptLib

#endif