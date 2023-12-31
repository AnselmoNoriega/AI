#include "Precompiled.h"
#include "GoalPersuitBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 GoalPersuitBehavior::Calculate(Agent& agent)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	float speed = 0.0f;

	if (distToDest > 1.0f)
	{
		const float decelTweaker = agent.mass * 1.5;
		speed = distToDest / 3.0f * decelTweaker;
		speed = X::Math::Min(speed, agent.maxSpeed);
	}

	const auto desiredVelocity = (agentToDest / distToDest) * speed;
	const auto arriveForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Red);
	}

	return arriveForce;
}

bool AI::GoalPersuitBehavior::CheckMemoryRecord(const Property& memory)
{
	X::Math::Vector2 pos = std::get<X::Math::Vector2>(memory);

	for (auto& property : properties)
	{
		if (property.x - 10 <= pos.x && property.x + 10 >= pos.x && property.y - 10 <= pos.y && property.y + 10 >= pos.y)
		{
			return false;
		}
	}

	return true;
}
