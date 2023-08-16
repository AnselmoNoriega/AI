#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	class SteeringModule final
	{
	public:
		SteeringModule(Agent& agent);

		template<class NewBehaviorType>
		NewBehaviorType* AddBehavior()
		{
			static_assert(std::is_base_of_v<SteeringBehavior, NewBehaviorType>, "SteeringBehavior doesnt dirive from SteeringBehavior");
			auto& newBehavior = mBehaviors.emplace_back(std::make_unique<NewBehaviorType>());
			return static_cast<NewBehaviorType*>(newBehavior.get());
		}

	private:
		Agent& mAgent;
		std::vector<std::unique_ptr<SteeringBehavior>> mBehaviors;
	};
}