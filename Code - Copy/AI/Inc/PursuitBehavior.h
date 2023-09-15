#pragma once
#include "SteeringBehavior.h"

namespace AI
{
	class PursuitBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};


	class EvadeBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		X::Math::Vector2 fov[3];
		bool hasFreeSight = true;
	};
}
