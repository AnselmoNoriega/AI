#pragma once
#include "PatrolStates.h"

void PatrolCharacter::Initialize()
{
	timePasssed = 0;
	timeToSpawnEnemy = 0;
	speed = 5;
	strength = 4;
	pos = { 0 ,0 };
	mStateMachine = new AI::StateMachine<PatrolCharacter>(*this);
	mStateMachine->AddState<Idle>();
	mStateMachine->AddState<Searching>();
	mStateMachine->AddState<Chasing>();
	mStateMachine->AddState<Attacking>();
	mStateMachine->AddState<CallingForHelp>();
	mStateMachine->ChangeState(0);
}

void PatrolCharacter::Update(float dt)
{
	mStateMachine->Update(dt);
}

void PatrolCharacter::ChangeState(PatrolStates newState)
{
	mStateMachine->ChangeState((int)newState);
}

void PatrolCharacter::Terminate()
{
	delete mStateMachine;
	mStateMachine = nullptr;

	if (enemy != nullptr)
	{
		delete enemy;
		enemy = nullptr;
	}
}

bool PatrolCharacter::isTimeToChangePos() const
{
	return timePasssed == 5;
}

bool PatrolCharacter::isEnemyStronger() const
{
	return enemy->strength > strength;
}

bool PatrolCharacter::isEnemyAround() const
{
	return enemy != nullptr;
}

bool PatrolCharacter::isEnemyClose() const
{
	float pointA = pow(pos.first, 2) + pow(pos.second, 2);
	float pointB = pow(enemy->pos.first, 2) + pow(enemy->pos.second, 2);

	float distance = pointB - pointA;
	return  distance > -200 && distance < 200;
}

bool PatrolCharacter::isEnemyDead()
{
	if (enemy->health <= 0)
	{
		delete enemy;
		enemy = nullptr;
		return true;
	}
}

void PatrolCharacter::IncreaseTimePassed(float time)
{
	if (timePasssed >= 5)
	{
		timePasssed = 0;
	}

	timePasssed += time;
}

void PatrolCharacter::IncreaseTimeToSpawnEnemy(float time)
{
	timeToSpawnEnemy += time;

	if (timeToSpawnEnemy >= 4)
	{
		enemy = new Enemy();
		time = 0;
	}
}

void PatrolCharacter::RunTowardEnemy()
{
	float tan = atan2(enemy->pos.second - pos.second, enemy->pos.first - pos.first);
	float x = speed * cos(tan);
	float y = speed * sin(tan);

	pos.first += x;
	pos.second += y;
}

void PatrolCharacter::AttackEnemy()
{
	--enemy->health;
}

void PatrolCharacter::StartMoving()
{
	//speed != 0
}

void PatrolCharacter::CallForHelp()
{
	//Calls for help
}

void PatrolCharacter::StopMoving()
{
	//speed = 0;
}

PatrolCharacter::Enemy::Enemy()
{
	health = 5;
	strength = 3;
	pos = { 5.0f, 5.0f };
}
