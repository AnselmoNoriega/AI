#pragma once
#include "SteeringBehavior.h"
#include "MemoryRecord.h"

namespace AI
{
	class GoalPersuitBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		bool CheckMemoryRecord(const Property& memory);

		std::vector<X::Math::Vector2> properties;
		float memoryImportance = 0;
	};

}
