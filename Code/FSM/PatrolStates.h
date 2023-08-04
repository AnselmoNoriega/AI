#pragma once
#include "AI.h"
#include "PatrolCharacter.h"

class Idle : public AI::State<PatrolCharacter>
{
public:
	void Enter(PatrolCharacter& agent) override
	{
		agent.StopMoving();
	}

	void Update(PatrolCharacter& agent, float dt) override
	{
		agent.IncreaseTimePassed(1);
		agent.IncreaseTimeToSpawnEnemy(1);

		if (agent.isEnemyAround())
		{
			if (agent.isEnemyStronger())
			{
				agent.ChangeState(PatrolStates::CALLINGFORHELP);
			}
			else
			{
				agent.ChangeState(PatrolStates::CHASING);
			}
		}
		else if (agent.isTimeToChangePos())
		{
			agent.ChangeState(PatrolStates::SEARCHING);
		}
	}

	void Exit(PatrolCharacter& agent) override
	{

	}

	void Debug() override
	{
		ImGui::Text("Idle");
	}
};

class Searching : public AI::State<PatrolCharacter>
{
public:
	void Enter(PatrolCharacter& agent) override
	{
		agent.StartMoving();
	}

	void Update(PatrolCharacter& agent, float dt) override
	{
		agent.IncreaseTimePassed(1);

		if (agent.isEnemyAround())
		{
			if (agent.isEnemyStronger())
			{
				agent.ChangeState(PatrolStates::CALLINGFORHELP);
			}
			else
			{
				agent.ChangeState(PatrolStates::CHASING);
			}
		}
		else if (agent.isTimeToChangePos())
		{
			agent.ChangeState(PatrolStates::IDLE);
		}
	}

	void Exit(PatrolCharacter& agent) override
	{

	}

	void Debug() override
	{
		ImGui::Text("Searching");
	}
};

class Chasing : public AI::State<PatrolCharacter>
{
public:
	void Enter(PatrolCharacter& agent) override
	{

	}

	void Update(PatrolCharacter& agent, float dt) override
	{
		agent.RunTowardEnemy();

		if (agent.isEnemyClose())
		{
			agent.ChangeState(PatrolStates::ATTACKING);
		}
	}

	void Exit(PatrolCharacter& agent) override
	{

	}

	void Debug() override
	{
		ImGui::Text("Chasing");
	}
};

class Attacking : public AI::State<PatrolCharacter>
{
public:
	void Enter(PatrolCharacter& agent) override
	{

	}

	void Update(PatrolCharacter& agent, float dt) override
	{
		agent.AttackEnemy();

		if (agent.isEnemyDead())
		{
			agent.ChangeState(PatrolStates::SEARCHING);
		}
	}

	void Exit(PatrolCharacter& agent) override
	{

	}

	void Debug() override
	{
		ImGui::Text("Attacking");
	}
};

class CallingForHelp : public AI::State<PatrolCharacter>
{
public:
	void Enter(PatrolCharacter& agent) override
	{
		agent.CallForHelp();
	}

	void Update(PatrolCharacter& agent, float dt) override
	{
		if (agent.isEnemyClose())
		{
			agent.ChangeState(PatrolStates::ATTACKING);
		}
		else
		{
			agent.ChangeState(PatrolStates::CHASING);
		}
	}

	void Exit(PatrolCharacter& agent) override
	{

	}

	void Debug() override
	{
		ImGui::Text("Calling For Help");
	}
};