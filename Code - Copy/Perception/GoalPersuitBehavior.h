#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	using Property = std::variant<int, float, X::Math::Vector2, bool>;

	class GoalPersuitBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		bool CheckMemoryRecord(const Property& memory);

		std::vector<Property> properties;
		float memoryImportance = 0;
	};

}
