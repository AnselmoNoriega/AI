#pragma once
#include "AI.h"
#include "Peon.h"

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
};

class Pursuing : public AI::State<Peon>
{
public:
	void Enter(Peon& agent) override
	{

	}

	void Update(Peon& agent, float dt) override
	{
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

		if (X::Math::Magnitude(agent.position - agent.destination)  < 5)
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
			agent.ChangeState(WANDER);
		}
	}

	void Exit(Peon& agent) override
	{
		if (timer <= 0.0f)
		{

		}
	}

	void Debug() override
	{

	}
};