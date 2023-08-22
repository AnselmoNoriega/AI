#include "Precompiled.h"
#include "WanderBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	auto newWanderTarget = mLocalWanderTarget + (X::RandomUnitCircle() * mWanderJitter);

	newWanderTarget = X::Math::Normalize(newWanderTarget);
	mLocalWanderTarget = newWanderTarget;

	const auto worldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);

	const auto agentDist = worldWanderTarget - agent.position;
	const float disToDest = X::Math::Magnitude(agentDist);
	if (disToDest <= 0.01f)
	{
		return X::Math::Vector2::Zero();
	}

	const auto desiredVelocity = (agentDist / disToDest) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	return seekForce;
}

void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}
