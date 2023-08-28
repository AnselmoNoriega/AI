#include "Precompiled.h"
#include "SteeringModule.h"
#include "Agent.h"

AI::SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

X::Math::Vector2 AI::SteeringModule::Calculate()
{
	X::Math::Vector2 totalForce;

	for (auto& behavior : mBehaviors)
	{
		if (behavior->IsActive()) 
		{
			totalForce += behavior->Calculate(mAgent) * behavior->GetWeight();
		}
	}

	X::Math::Vector2 separationForce;
	for (auto& n : mAgent.neighbors)
	{
		if (n != mAgent.target)
		{
			auto dirToNeighbor = n->position - mAgent.position;
			auto distance = X::Math::Magnitude(dirToNeighbor);
			auto overlapDistance = (n->radius + mAgent.radius) - distance;
			if (overlapDistance > 0.0f)
			{
				dirToNeighbor /= distance;
				separationForce += (-dirToNeighbor * ((overlapDistance / mAgent.radius) * mAgent.maxSpeed));
			}
		}
	}
	return totalForce + separationForce;
}
