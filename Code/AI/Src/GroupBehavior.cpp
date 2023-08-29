#include "Precompiled.h"
#include "GroupBehavior.h"
#include "Agent.h"

X::Math::Vector2 AI::SeparationBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 separationForce;
	for (auto& n : agent.neighbors)
	{
		if (n != agent.target)
		{
			auto dirToNeighbor = n->position - agent.position;
			auto distance = X::Math::Magnitude(dirToNeighbor);
			auto overlapDistance = (n->radius + agent.radius) - distance;

			if (overlapDistance > 0.0f)
			{
				dirToNeighbor /= distance;
				if (X::Math::Dot(dirToNeighbor, agent.heading) > 0.0f)
				{
					separationForce += (-dirToNeighbor * ((overlapDistance / agent.radius) * agent.maxSpeed));
				}
			}
		}
	}

	if (IsDebug())
	{
		X::DrawScreenCircle(agent.position, agent.radius, X::Colors::SpringGreen);
	}

	return separationForce;
}
