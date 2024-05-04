#ifndef ANNEALING_H
#define ANNEALING_H

namespace OptLib
{
	namespace ConcreteOptimizer
	{
		template<size_t dim>
		class Annealing: OptimizerInterface::OptimizerAlgorithm<dim>{
		public:
			static PointVal<dim> Proceed(ConcreteState::StateStochastic<dim>& State, const FuncInterface::IFunc<dim>* f)
			{
				State.UpdateState();
				return State.Guess();
			}
		};
	}
	namespace StateParams
	{
		template<size_t dim>
		struct AnnealingParams
		{
		protected:
			double h;
			double endTemperature;
			double initialTemperature;
			double (*TemperatureFunction) (double, int);
			Point<dim> currentPoint;
		public:
			using OptAlgo = OptLib::ConcreteOptimizer::Annealing<dim>;
			using StateType = OptLib::ConcreteState::StateStochastic<dim>;
			AnnealingParams(Point<dim>&& sop, double step, double temperature_end) :
				h{ step }, endTemperature{ temperature_end }, currentPoint{ std::move(sop) } {}
			StateType CreateState(FuncInterface::IFunc<dim>* f)
			{
				state = new StateStochastic<dim>(std::move(currentPoint), f, initialTemperature, TemperatureFunction);
				return state;
			}
		};
	}
}

#endif