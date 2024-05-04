#ifndef OVERALLOPTIMIZER_H
#define OVERALLOPTIMIZER_H

#include "OptimizerInterface.h"

namespace OptLib
{
	struct OptimizerParams
	{
		double eps_f, eps_x;
		size_t max_iter;
	};

	template<typename state>
	class Optimizer
	{
	public:
		constexpr static size_t arg_count = state::arg_count;
		
		using func = typename state::func_type;

		double tol_f() { return Prm.eps_f; }
		double tol_x() { return Prm.eps_x; }
		size_t MaxIterCount() { return Prm.max_iter; }
		size_t CurIterCount() { return s; }
		const PointVal<arg_count>& CurrentGuess() { return State->Guess(); }

	public:
		Optimizer(state* State_, func* f_, const OptimizerParams& prm) :
			State{State_},
			f{f_},
			Prm{ prm },
			s{ 0 }
			{}

		template<typename algo>
		const PointVal<arg_count>& Optimize()
		{
#ifdef DEBUG_LIB
			std::cout << "Optimization started...\n";
#endif // DEBUG_LIB

			// TODO : separate thread
			bool g = false;
			while (!g &&
				s < MaxIterCount())
			{
#ifdef DEBUG_LIB
				std::cout << "Current state: " << State->Guess() << "\n";
#endif // DEBUG_LIB
				OptimizerInterface::OptimizerAlgorithm<arg_count>::Proceed<algo, state, func>(State, f);
				++s;
				g = OptimizerInterface::OptimizerAlgorithm<arg_count>::IsConverged(State, tol_x(), tol_x());
			}
#ifdef DEBUG_LIB
			std::cout << "Optimization ended\n";
			std::cout << "Total number of iterations is s = " << CurIterCount() << '\n';
			std::cout << "Final guess is x = " << CurrentGuess() << '\n';
#endif // DEBUG_LIB

			return CurrentGuess();
		}

		template<typename algo>
		PointVal<arg_count> Continue(double eps_x, double eps_f)
		{
			Prm.eps_f = eps_f;
			Prm.eps_x = eps_x;
			return Optimize<algo>();
		}

	protected:
		state* State;
		func* f;

		size_t s; // current number of iterations
		OptimizerParams Prm;
	};

	template<size_t dim,
		typename state,
		template<size_t dim> typename func>
	class Optimizer1Step
	{
	protected:
		state* State;
		const func<dim>* f;
	public:
		Optimizer1Step(state* State_, const func<dim>* f_) :
			State{ State_ },
			f{ f_ }{}
		PointVal<dim> CurrentGuess() { return State->Guess(); }

		template<typename algo>
		PointVal<dim> Optimize()
		{
			OptimizerInterface::OptimizerAlgorithm<dim>::Proceed<algo, state, func>(State, f);
			return CurrentGuess();
		}
	};
} // OptLib
#endif