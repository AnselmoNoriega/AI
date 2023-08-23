#pragma once

#include <AI.h>

class Peon : public AI::Agent
{
public:
	Peon(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float dt);
	void Render();

	void ShowDebug(bool debug);

	void SetArrive(bool active) { mArriveBehavior->SetActive(active); }
	void SetEvade(bool active) { mEvadeBehavior->SetActive(active); }
	void SetPursuit(bool active) { mPursuitBehavior->SetActive(active); }
	void SetFlee(bool active) { mFleeBehaivior->SetActive(active); }
	void SetSeek(bool active) { mSeekBehaivior->SetActive(active); }
	void SetWander(bool active) { mWanderBehavior->SetActive(active); }

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::EvadeBehavior* mEvadeBehavior = nullptr;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::FleeBehavior* mFleeBehaivior = nullptr;
	AI::SeekBehavior* mSeekBehaivior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	std::array<X::TextureId, 16> mTextureIDs;
};