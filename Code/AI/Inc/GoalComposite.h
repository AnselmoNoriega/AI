#pragma once
#include "Goal.h"

namespace AI
{
	template<class AgentType>
	class GoalComposite : public Goal<AgentType>
	{
	public:
		using Status = Goal<AgentType>::Status;
		GoalComposite(AgentType& agent)
			: Goal<AgentType>(agent)
		{

		}

		virtual ~GoalComposite()
		{
			RemoveAllSubObjects();
		}

	protected:
		template<class GoalType>
		void AddSubGoal()
		{
			static_assert(std::is_base_of_v<Goal, GoalType>, "GoalComposite: Doesnt dirive from 'Goal'");
			SubGoals.push_front(std::make_unique<GoalType>());
		}

		void RemoveAllSubObjects()
		{
			for (auto& goal : mSubgoals)
			{
				goal->Terminate();
			}
			mSubGoals.clear();
		}

		Status ProcessSubgoals()
		{
			while (!mSubgoals.empty())
			{
				auto& goal = mSubgoals.front();
				if (goal->mStatus != Status::COMPLETED && goal->mStatus != Status::FAILED)
				{
					break;
				}

				goal->Terminate();
				mSubgoals.pop_front();
			}

			if (!mSubgoals.empty())
			{
				Status status = mSubgoal.front()->Process();
				if (status == Status::COMPLITED && mSubgoals.size() > 1)
				{
					return Status::ACTIVE;
				}

				return status;
			}

			return Status::COMPLETED;
		}

		using SubGoals = std::list<std::unique_ptr<Goal<AgentType>>>;
		SubGoals mSubgoals;
	};
}