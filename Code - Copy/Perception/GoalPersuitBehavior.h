#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	class GoalPersuitBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		float memoryImportance = 0;
	};

}
