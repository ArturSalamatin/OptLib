#ifndef STATE_H
#define STATE_H

#include <algorithm>
#include "../Points/SetOfPoints/PointVals/Point/Point.h"
#include "../Points/SetOfPoints/PointVals/PointVal.h"
#include "../Points/SetOfPoints/SetOfPoints.h"
#include "../Points/Definitions.h"
#include "../Functions/Interface/FuncInterface.h"
#include "StateInterface.h"

namespace OptLib
{
	namespace ConcreteState
	{
		/// <summary>
		/// Direct methods require sorted simplex points with respect to f(x)
		/// </summary>
		template<size_t dim>
		using StateDirect =  StateInterface::IStateSimplex<dim, SimplexValSort<dim>>;

		/// <summary>
		/// Simplexes for direct methods on segments (in 1D) must not be sorted with respect to f(x). Must be sorted with respect to x == x[0]
		/// </summary>
		class StateSegment : public StateInterface::IStateSimplex<1, SimplexValNoSort<1>>
		{
		public:
			StateSegment(const StateSegment&) = default;
			StateSegment(const Simplex<1>& State, const FuncInterface::IFunc<1>* f)
				:
				StateInterface::IStateSimplex<1, SimplexValNoSort<1>>(
					OrderPointsInSegment(State), f)
			{}

		protected:
			auto OrderPointsInSegment(Simplex<1> setOfPoints) -> Simplex<1>
			{
				if (setOfPoints[0][0] > setOfPoints[1][0])
					std::swap(setOfPoints[0], setOfPoints[1]);
				return setOfPoints;
			}
		};

		/// <summary>
		/// First and second order methods require only a point rather than entire simplex for optimization
		/// </summary>
		template<size_t dim>
		class StatePoint : public StateInterface::IState<dim>
		{
		protected:
			PointVal<dim> dx{};
		public:

			using StateInterface::IState<dim>::IState;

			bool IsConverged(double abs_tol, double rel_tol) const override
			{
				auto& std = dx;
				auto var{ abs<dim>(dx / Guess()) };
				for (size_t i = 0; i < dim; ++i)
				{
					bool f = (std[i] < abs_tol) || (var[i] < rel_tol);
					if (!f) return false;
				}
				return (std.Val < abs_tol) || (var.Val < rel_tol);
			}

			virtual void UpdateState(const PointVal<dim>& v)
			{
				dx = abs<dim>(v - Guess());
				ItsGuess = v;
			}
		};

		/// <summary>
		/// Stochastic methods require multiple initial points
		/// </summary>
		template<size_t dim>
		class StateStochastic : public StateInterface::IState<dim>
		{
		protected:
			double(*Temperature) (double, int);
			int iteration;
			double endTemperature;
			double h;
		public:
			double temperature;
			PointVal<dim> NextRandomState()
			{
				PointVal<dim> x = Guess();
				for (int i = 0; i < dim; i++) {
					double r = ((double)rand() / RAND_MAX);
					x.P[i] = 2.0 * r * h + x.P[i] - h;
				}
				return x;
			}
			PointVal<dim> bestGuess;
			StateStochastic(
				OptLib::Point<dim>&& State, 
				FuncInterface::IFunc<dim>* f, 
				double initialTemperature, 
				double (*TemperatureFunction) (double, int), 
				double step, 
				double temperature_end) :
				//StateInterface::IState<dim>(std::move(State), f), 
				temperature{ initialTemperature }, Temperature{ TemperatureFunction }, h{ step }, endTemperature{ temperature_end },iteration{ 0 } 
			{
				ItsGuess = FuncInterface::CreateFromPoint(std::move(State), f);
				bestGuess = ItsGuess;
			}
			bool IsConverged(double endTemperature, double) const override
			{
				return temperature < endTemperature;
			}
			void ChangeGuess(const PointVal<dim>& currentGuess) {
				ItsGuess = currentGuess;
			}
			void UpdateState()
			{
				iteration++;
				temperature = Temperature(temperature, iteration);
				PointVal<dim> currentGuess = NextRandomState(); //{ FuncInterface::CreateFromPoint(NextRandomState(Guess().P, h), f) };
				//UpdateState();
				double dp = exp((Guess().Val - currentGuess.Val) / temperature);
				if (dp > 1)
				{
					ChangeGuess(currentGuess);
				}
				else
				{
					double p = (double)rand() / RAND_MAX;
					if (dp > p)
					{
						ChangeGuess(currentGuess);
					}
				}
				if (currentGuess < bestGuess) bestGuess = currentGuess;
			}
		};
	} // ConcreteState
} // OptLib

#endif