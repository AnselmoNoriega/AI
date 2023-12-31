#pragma once
#include "AI.h"
#include "Peon.h"
#include "Wolf.h"

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

class Wander : public AI::State<Peon>
{
public:
	void Enter(Peon& agent) override
	{

	}

	void Update(Peon& agent, float dt) override
	{
		if (!CollisionCheck(agent))
		{
			agent.mEvadeBehavior->SetActive(true);
			agent.mWanderBehavior->SetActive(false);
			agent.mWanderBehavior->mLocalWanderTarget = X::Math::Vector2::Zero();
		}
		else
		{
			agent.mEvadeBehavior->SetActive(false);
			agent.mWanderBehavior->SetActive(true);
		}

		if (agent.mWanderBehavior->IsActive())
		{
			agent.mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
		}

		const auto force = agent.mSteeringModule->Calculate();
		const auto acceleration = force / agent.mass;
		agent.velocity += acceleration * dt;

		if (X::Math::MagnitudeSqr(agent.velocity) > 1.0f)
		{
			agent.heading = X::Math::Normalize(agent.velocity);
		}

		agent.position += agent.velocity * dt;

		const auto screenWidth = X::GetScreenWidth();
		const auto screenHeight = X::GetScreenHeight();

		if (agent.position.x < 0.0f)
		{
			agent.position.x += screenWidth;
		}
		if (agent.position.x >= screenWidth)
		{
			agent.position.x -= screenWidth;
		}
		if (agent.position.y < 0.0f)
		{
			agent.position.y += screenHeight;
		}
		if (agent.position.y >= screenHeight)
		{
			agent.position.y -= screenHeight;
		}
	}

	void Exit(Peon& agent) override
	{

	}

	void Debug() override
	{

	}

	bool CollisionCheck(Peon& agent)
	{
		X::Math::Vector2 fov[3];

		fov[0] = X::Math::Rotate(agent.heading * 60, 0);
		fov[1] = X::Math::Rotate(agent.heading * 60, -0.8f);
		fov[2] = X::Math::Rotate(agent.heading * 60, 0.8f);

		int i;
		bool hasFreeSight;

		for (i = 0; i < 3; ++i)
		{
			X::Math::LineSegment lineToTarget(agent.position, agent.position + fov[i]);
			hasFreeSight = agent.world.HasLineOfSight(lineToTarget);
			if (!hasFreeSight) break;
		}

		return hasFreeSight;
	}
};

class Pursuing : public AI::State<Peon>
{
public:
	void Enter(Peon& agent) override
	{

	}

	void Update(Peon& agent, float dt) override
	{
		if (!CollisionCheck(agent))
		{
			agent.mEvadeBehavior->SetActive(true);
			agent.mGoalPersuitBehavior->SetActive(false);
			agent.mWanderBehavior->mLocalWanderTarget = X::Math::Vector2::Zero();
		}
		else
		{
			agent.mEvadeBehavior->SetActive(false);
			agent.mGoalPersuitBehavior->SetActive(true);
		}

		const auto force = agent.mSteeringModule->Calculate();
		const auto acceleration = force / agent.mass;
		agent.velocity += acceleration * dt;

		if (X::Math::MagnitudeSqr(agent.velocity) > 1.0f)
		{
			agent.heading = X::Math::Normalize(agent.velocity);
		}

		agent.position += agent.velocity * dt;

		const auto screenWidth = X::GetScreenWidth();
		const auto screenHeight = X::GetScreenHeight();

		if (agent.position.x < 0.0f)
		{
			agent.position.x += screenWidth;
		}
		if (agent.position.x >= screenWidth)
		{
			agent.position.x -= screenWidth;
		}
		if (agent.position.y < 0.0f)
		{
			agent.position.y += screenHeight;
		}
		if (agent.position.y >= screenHeight)
		{
			agent.position.y -= screenHeight;
		}

		if (X::Math::Magnitude(agent.position - agent.destination)  < 5 && X::Math::Magnitude(agent.position - agent.destination) > -5)
		{
			agent.ChangeState(WAITING);
		}
	}

	void Exit(Peon& agent) override
	{

	}

	void Debug() override
	{

	}

	bool CollisionCheck(Peon& agent)
	{
		X::Math::Vector2 fov[3];

		fov[0] = X::Math::Rotate(agent.heading * 60, 0);
		fov[1] = X::Math::Rotate(agent.heading * 60, -0.8f);
		fov[2] = X::Math::Rotate(agent.heading * 60, 0.8f);

		int i;
		bool hasFreeSight;

		for (i = 0; i < 3; ++i)
		{
			X::Math::LineSegment lineToTarget(agent.position, agent.position + fov[i]);
			hasFreeSight = agent.world.HasLineOfSight(lineToTarget);
			if (!hasFreeSight) break;
		}

		return hasFreeSight;
	}
};

class Waiting : public AI::State<Peon>
{
private:
	float timer;

public:
	void Enter(Peon& agent) override
	{
		timer = 10;
	}

	void Update(Peon& agent, float dt) override
	{
		timer -= dt;

		if (timer <= 0.0f)
		{
			agent.target = nullptr;
			agent.ChangeState(WANDER);
			agent.SetWander(true);
			agent.SetGoal(false);
			agent.mWanderBehavior->SetActive(true);
			agent.mGoalPersuitBehavior->memoryImportance = 0.0f;
		}
	}

	void Exit(Peon& agent) override
	{
		if (timer <= 0.0f)
		{
			agent.mGoalPersuitBehavior->properties.push_back(agent.position);
		}
	}

	void Debug() override
	{

	}
};

//----------------------------------------------------wolfStates----------------------------------------------------------------

class Looking : public AI::State<Wolf>
{
public:
	void Enter(Wolf& agent) override
	{

	}

	void Update(Wolf& agent, float dt) override
	{
		if (!CollisionCheck(agent))
		{
			agent.mEvadeBehavior->SetActive(true);
			agent.mWanderBehavior->SetActive(false);
			agent.mWanderBehavior->mLocalWanderTarget = X::Math::Vector2::Zero();
		}
		else
		{
			agent.mEvadeBehavior->SetActive(false);
			agent.mWanderBehavior->SetActive(true);
		}

		if (agent.mWanderBehavior->IsActive())
		{
			agent.mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
		}

		const auto force = agent.mSteeringModule->Calculate();
		const auto acceleration = force / agent.mass;
		agent.velocity += acceleration * dt;

		if (X::Math::MagnitudeSqr(agent.velocity) > 1.0f)
		{
			agent.heading = X::Math::Normalize(agent.velocity);
		}

		agent.position += agent.velocity * dt;

		const auto screenWidth = X::GetScreenWidth();
		const auto screenHeight = X::GetScreenHeight();

		if (agent.position.x < 0.0f)
		{
			agent.position.x += screenWidth;
		}
		if (agent.position.x >= screenWidth)
		{
			agent.position.x -= screenWidth;
		}
		if (agent.position.y < 0.0f)
		{
			agent.position.y += screenHeight;
		}
		if (agent.position.y >= screenHeight)
		{
			agent.position.y -= screenHeight;
		}
	}

	void Exit(Wolf& agent) override
	{

	}

	void Debug() override
	{

	}

	bool CollisionCheck(Wolf& agent)
	{
		X::Math::Vector2 fov[3];

		fov[0] = X::Math::Rotate(agent.heading * 60, 0);
		fov[1] = X::Math::Rotate(agent.heading * 60, -0.8f);
		fov[2] = X::Math::Rotate(agent.heading * 60, 0.8f);

		int i;
		bool hasFreeSight;

		for (i = 0; i < 3; ++i)
		{
			X::Math::LineSegment lineToTarget(agent.position, agent.position + fov[i]);
			hasFreeSight = agent.world.HasLineOfSight(lineToTarget);
			if (!hasFreeSight) break;
		}

		return hasFreeSight;
	}
};

class Chasing : public AI::State<Wolf>
{
public:
	void Enter(Wolf& agent) override
	{

	}

	void Update(Wolf& agent, float dt) override
	{
		if (!CollisionCheck(agent))
		{
			agent.mEvadeBehavior->SetActive(true);
			agent.mPursuitBehavior->SetActive(false);
			agent.mWanderBehavior->mLocalWanderTarget = X::Math::Vector2::Zero();
		}
		else
		{
			agent.mEvadeBehavior->SetActive(false);
			agent.mPursuitBehavior->SetActive(true);
		}

		const auto force = agent.mSteeringModule->Calculate();
		const auto acceleration = force / agent.mass;
		agent.velocity += acceleration * dt;

		if (X::Math::MagnitudeSqr(agent.velocity) > 1.0f)
		{
			agent.heading = X::Math::Normalize(agent.velocity);
		}

		agent.position += agent.velocity * dt;

		const auto screenWidth = X::GetScreenWidth();
		const auto screenHeight = X::GetScreenHeight();

		if (agent.position.x < 0.0f)
		{
			agent.position.x += screenWidth;
		}
		if (agent.position.x >= screenWidth)
		{
			agent.position.x -= screenWidth;
		}
		if (agent.position.y < 0.0f)
		{
			agent.position.y += screenHeight;
		}
		if (agent.position.y >= screenHeight)
		{
			agent.position.y -= screenHeight;
		}
		auto distance = X::Math::Magnitude(agent.position - agent.target->position);
		if ((distance < 10 && distance > -10) || (distance > 500 || distance < -500) || agent.target == nullptr)
		{
			agent.KillPeon(agent.target);
			agent.target = nullptr;
			agent.ChangeState(LOOKING);
			agent.SetWander(true);
			agent.mWanderBehavior->SetActive(true);
			agent.mPursuitBehavior->SetActive(false);
		}
	}

	void Exit(Wolf& agent) override
	{

	}

	void Debug() override
	{

	}

	bool CollisionCheck(Wolf& agent)
	{
		X::Math::Vector2 fov[3];

		fov[0] = X::Math::Rotate(agent.heading * 60, 0);
		fov[1] = X::Math::Rotate(agent.heading * 60, -0.8f);
		fov[2] = X::Math::Rotate(agent.heading * 60, 0.8f);

		int i;
		bool hasFreeSight;

		for (i = 0; i < 3; ++i)
		{
			X::Math::LineSegment lineToTarget(agent.position, agent.position + fov[i]);
			hasFreeSight = agent.world.HasLineOfSight(lineToTarget);
			if (!hasFreeSight) break;
		}

		return hasFreeSight;
	}
};