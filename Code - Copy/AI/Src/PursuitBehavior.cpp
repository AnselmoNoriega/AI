#include "Precompiled.h"
#include "PursuitBehavior.h"
#include "AIWorld.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 PursuitBehavior::Calculate(Agent& agent)
{
	const auto agentToDest = agent.target->position - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);

	if (distToDest <= 0.1f)
	{
		return X::Math::Vector2::Zero();
	}

	const auto desiredVelocity = (agentToDest / distToDest) * agent.maxSpeed;
	const auto pursiutForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenCircle(agent.target->position, 20.0f, X::Colors::Red);
	}

	return pursiutForce;
}

X::Math::Vector2 EvadeBehavior::Calculate(Agent& agent)
{
	fov[0] = X::Math::Rotate(agent.heading * 60, 0);
	fov[1] = X::Math::Rotate(agent.heading * 60, -0.8f);
	fov[2] = X::Math::Rotate(agent.heading * 60, 0.8f);

	int i;

	for (i = 0; i < 3; ++i)
	{
		X::Math::LineSegment lineToTarget(agent.position, agent.position + fov[i]);
		hasFreeSight = agent.world.HasLineOfSight(lineToTarget);
		if (!hasFreeSight) break;
	}

	X::Math::Vector2 desiredVelocity = X::Math::Vector2::Zero();

	if (!hasFreeSight)
	{
		const auto agentToDest = fov[i];
		const float distToDest = X::Math::Magnitude(agentToDest);
		desiredVelocity = -(agentToDest / distToDest) * agent.maxSpeed;
	}
	
	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenCircle(agent.position + fov[i], 5.0f, X::Colors::Red);

		X::DrawScreenLine(agent.position, agent.position + fov[0], X::Colors::DarkViolet);
		X::DrawScreenLine(agent.position, agent.position + fov[1], X::Colors::DarkViolet);
		X::DrawScreenLine(agent.position, agent.position + fov[2], X::Colors::DarkViolet);
	}
	return desiredVelocity - agent.velocity;
}