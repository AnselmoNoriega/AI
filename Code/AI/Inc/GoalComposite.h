#pragma once
#include "Goal.h"

namespace AI
{
	template<class AgentType>
	class GoalComposite : public Goal<AgentType>
	{

		GoalComposite(AgentType& agent)
			: Goal<AgentType>(agent)
		{

		}

		virtual ~GoalComposite();

	protected:
		template<class GoalType>
		void AddSubGoal()
		{
			static_assert(std::is_base_of_v<Goal, GoalType>, "GoalComposite: Doesnt dirive from 'Goal'");
			SubGoals.push_front(std::make_unique<GoalType>());
		}

		using SubGoals = std::list<std::unique_ptr<Goal<AgentType>>>;
		SubGoal mSubgoals;
	};
}