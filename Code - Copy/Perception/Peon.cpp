#include "Peon.h"
#include "TypeIDs.h"

#include"VisualSensor.h"
#include "TypeIDs.h"

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

extern float viewRange;
extern float viewAngle;

namespace
{
	float ComputeImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
	{
		Types entityType = (Types)record.GetProperty<int>("type");

		switch (entityType)
		{
		case Types::Invalid:
			return 0;
		case Types::PeonID:
		{
			float distance = X::Math::Distance(agent.position, record.GetProperty<X::Math::Vector2>("lastSeenPosition"));
			float distanceScore = std::max(1000.0f - distance, 0.0f);
			return distanceScore;
		}
		break;
		case Types::MineralID:
		{
			float distance = X::Math::Distance(agent.position, record.GetProperty<X::Math::Vector2>("lastSeenPosition"));
			float distanceScore = std::max(10000.0f - distance, 0.0f);
			return distanceScore;
		}
		break;
		default:
			break;
		}

		return 0;
	}
}

Peon::Peon(AI::AIWorld& world)
	: Agent(world, Types::PeonID)
{
}

void Peon::Load()
{
	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mPerceptionModule->SetMomorySpan(3.0f);
	mVisualSensor = mPerceptionModule->AddSensore<VisualSensor>();
	mVisualSensor->targetType = Types::MineralID;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mGoalPersuitBehavior = mSteeringModule->AddBehavior<AI::GoalPersuitBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
	mWanderBehavior->SetActive(true);

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
	mVisualSensor->viewRange = viewRange;
	mVisualSensor->viewHalfAngle = viewAngle * X::Math::kDegToRad;

	mPerceptionModule->Update(dt);

	if (mWanderBehavior->IsActive())
	{
		mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
	}
	else if (mGoalPersuitBehavior->IsActive())
	{

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

	const auto& memoryRecords = mPerceptionModule->GetMemoryRecords();
	for (auto& memory : memoryRecords)
	{
		auto pos = memory.GetProperty<X::Math::Vector2>("lastSeenPosition");
		X::DrawScreenLine(position, pos, X::Colors::Red);

		if (mGoalPersuitBehavior->memoryImportance < memory.importance)
		{
			SetWander(false);
			SetGoal(true);
			mGoalPersuitBehavior->memoryImportance = memory.importance;
			destination = pos;
		}

		std::string score = std::to_string(memory.importance);
		X::DrawScreenText(score.c_str(), pos.x, pos.y, 12.0f, X::Colors::White);
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
	mGoalPersuitBehavior->ShowDebug(debug);
	mWanderBehavior->ShowDebug(debug);
}
