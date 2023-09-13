#pragma once

#include <AI.h>

class VisualSensor;

enum WolfStates
{
	LOOKING,
	CHASING
};

class Wolf : public AI::Agent
{
public:
	Wolf(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float dt);
	void Render();

	void ShowDebug(bool debug);

	void SetPursuit(bool active) { mPursuitBehavior->SetActive(active); }
	void SetWander(bool active) { mWanderBehavior->SetActive(active); }

	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;

	void ChangeState(WolfStates newState);
	WolfStates state;
private:

	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;

	VisualSensor* mVisualSensor = nullptr;
	std::array<X::TextureId, 16> mTextureIDs;

	AI::StateMachine<Wolf>* mStateMachine;
	void Terminate();
};