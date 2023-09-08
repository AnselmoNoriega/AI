#pragma once
#include <AI.h>
#include "ImGui/Inc/imgui.h"
#include "XMath.h"

enum PatrolStates
{
	IDLE,
	SEARCHING,
	CHASING,
	ATTACKING,
	CALLINGFORHELP
};

class PatrolCharacter
{
public:
	class Enemy
	{
	public:
		Enemy();

		int health;
		int strength;
		std::pair<float, float> pos;
	};

	void Initialize();
	void Terminate();
	void Update(float dt);
	void Debug();
	void ChangeState(PatrolStates newState);

	bool isTimeToChangePos() const;
	bool isEnemyStronger() const;
	bool isEnemyAround() const;
	bool isEnemyClose() const;
	bool isEnemyDead();

	void IncreaseTimePassed(float time);
	void IncreaseTimeToSpawnEnemy(float time);
	void RunTowardEnemy();
	void AttackEnemy();
	void StartMoving();
	void CallForHelp();
	void StopMoving();

private:
	AI::StateMachine<PatrolCharacter>* mStateMachine;
	float timePasssed;
	float timeToSpawnEnemy;
	float speed;
	int strength;
	Enemy* enemy;
	std::pair<float, float> pos;

};
