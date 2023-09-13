#include "Precompiled.h"
#include "WanderBehavior.h"
#include "AIWorld.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
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

		if (IsDebug())
		{
			X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
			X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
			X::DrawScreenCircle(fov[i], 20.0f, X::Colors::Red);

			X::DrawScreenLine(agent.position, agent.position + fov[0], X::Colors::DarkViolet);
			X::DrawScreenLine(agent.position, agent.position + fov[1], X::Colors::DarkViolet);
			X::DrawScreenLine(agent.position, agent.position + fov[2], X::Colors::DarkViolet);
		}

		return desiredVelocity - agent.velocity;
	}
	else
	{
		X::Math::Vector2 newWanderTarget = mLocalWanderTarget + (X::RandomUnitCircle() * mWanderJitter);
		newWanderTarget = X::Math::Normalize(newWanderTarget) * mWanderRadius;
		mLocalWanderTarget = newWanderTarget;

		newWanderTarget += X::Math::Vector2(0.0f, mWanderDistance);

		const auto worldTransform = agent.GetWorldTransform();
		const auto worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);

		const auto agentDist = worldWanderTarget - agent.position;
		const float disToDest = X::Math::Magnitude(agentDist);

		if (disToDest <= 0.01f)
		{
			return X::Math::Vector2::Zero();
		}
		const auto desiredVelocity = (agentDist / disToDest) * agent.maxSpeed;

		if (IsDebug())
		{
			const auto wanderCenter = X::Math::TransformCoord({ 0.0f, mWanderDistance }, worldTransform);
			X::DrawScreenCircle(wanderCenter, mWanderRadius, X::Colors::Yellow);
			X::DrawScreenDiamond(worldWanderTarget, 3.0f, X::Colors::Red);
			X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);

			X::DrawScreenLine(agent.position, agent.position + fov[0], X::Colors::DarkViolet);
			X::DrawScreenLine(agent.position, agent.position + fov[1], X::Colors::DarkViolet);
			X::DrawScreenLine(agent.position, agent.position + fov[2], X::Colors::DarkViolet);
		}

		return desiredVelocity - agent.velocity;
	}
}

void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}
