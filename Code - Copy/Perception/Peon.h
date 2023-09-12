#pragma once

#include <AI.h>

class VisualSensor;

enum PeonStates
{
	WANDER,
	PURSIUNG,
	WAITING
};

class Peon : public AI::Agent
{
public:
	Peon(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float dt);
	void Render();

	void ShowDebug(bool debug);

	void SetGoal(bool active) { mGoalPersuitBehavior->SetActive(active); }
	void SetWander(bool active) { mWanderBehavior->SetActive(active); }

	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::GoalPersuitBehavior* mGoalPersuitBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;

	void ChangeState(PeonStates newState);
	PeonStates state;
private:

	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;

	VisualSensor* mVisualSensor = nullptr;
	std::array<X::TextureId, 16> mTextureIDs;

	AI::StateMachine<Peon>* mStateMachine;
	void Terminate();
};