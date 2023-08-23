#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	class ArriveBehavior : public SteeringBehavior
	{
	public:
		enum class Deceleration
		{
			Fast,
			Normal,
			Slow
		};

		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}