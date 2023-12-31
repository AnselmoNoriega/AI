#include "Peon.h"
#include "TypeIDs.h"

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

Peon::Peon(AI::AIWorld& world)
	: Agent(world, Types::PeonID)
{
}

void Peon::Load()
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();
	mEvadeBehavior = mSteeringModule->AddBehavior<AI::EvadeBehavior>();
	mPursuitBehavior = mSteeringModule->AddBehavior<AI::PursuitBehavior>();
	mFleeBehaivior = mSteeringModule->AddBehavior<AI::FleeBehavior>();
	mSeekBehaivior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
	mSeparationBehavior = mSteeringModule->AddBehavior<AI::SeparationBehavior>();
	mAlignmentBehavior = mSteeringModule->AddBehavior<AI::AlignmentBehavior>();
	mCohesionBehavior = mSteeringModule->AddBehavior<AI::CohesionBehavior>();
	mWanderBehavior->SetActive(true);
	mSeparationBehavior->SetActive(true);
	mAlignmentBehavior->SetActive(true);
	mCohesionBehavior->SetActive(true);

	for (int i = 0; i < mTextureIDs.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "scv_%02i.png", i + 1);
		mTextureIDs[i] = X::LoadTexture(name);
	}

	float spriteWidth = X::GetSpriteWidth(mTextureIDs[0]);
	radius = spriteWidth;
}

void Peon::Unload()
{

}

void Peon::Update(float dt)
{
	if (mWanderBehavior->IsActive())
	{
		mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
	}

	const auto force = mSteeringModule->Calculate();
	const auto acceleration = force / mass;
	velocity += acceleration * dt;

	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
	{
		heading = X::Math::Normalize(velocity);
	}

	position += velocity * dt;

	const auto screenWidth = X::GetScreenWidth();
	const auto screenHeight = X::GetScreenHeight();

	if (position.x < 0.0f)
	{
		position.x += screenWidth;
	}
	if (position.x >= screenWidth)
	{
		position.x -= screenWidth;
	}
	if (position.y < 0.0f)
	{
		position.y += screenHeight;
	}			 
	if (position.y >= screenHeight)
	{			 
		position.y -= screenHeight;
	}
}

void Peon::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTextureIDs.size()) % mTextureIDs.size();
	X::DrawSprite(mTextureIDs[frame], position);
}

void Peon::ShowDebug(bool debug)
{
	mArriveBehavior->ShowDebug(debug);
	mEvadeBehavior->ShowDebug(debug);
	mPursuitBehavior->ShowDebug(debug);
	mFleeBehaivior->ShowDebug(debug);
	mSeekBehaivior->ShowDebug(debug);
	mWanderBehavior->ShowDebug(debug);
	mSeparationBehavior->ShowDebug(debug);
	mAlignmentBehavior->ShowDebug(debug);
	mCohesionBehavior->ShowDebug(debug);
}
