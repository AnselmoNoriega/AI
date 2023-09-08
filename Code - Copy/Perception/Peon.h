#pragma once

#include <AI.h>
class VisualSensor;

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

private:
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;

	AI::GoalPersuitBehavior* mGoalPersuitBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;

	VisualSensor* mVisualSensor = nullptr;
	std::array<X::TextureId, 16> mTextureIDs;
};