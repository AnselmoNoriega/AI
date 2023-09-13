#include "Wolf.h"
#include "TypeIDs.h"

#include"VisualSensor.h"
#include "TypeIDs.h"

#include "States.h"

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
		case Types::WolfID:
		{
			float distance = X::Math::Distance(agent.position, record.GetProperty<X::Math::Vector2>("lastSeenPosition"));
			float distanceScore = std::max(1000.0f - distance, 0.0f);
			return distanceScore;
		}
		break;
		case Types::PeonID:
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

Wolf::Wolf(AI::AIWorld& world)
	: Agent(world, Types::WolfID)
{
}

void Wolf::Load()
{
	mStateMachine = new AI::StateMachine<Wolf>(*this);
	mStateMachine->AddState<Wander<Wolf>>(); 
	mStateMachine->AddState<Chasing>();
	mStateMachine->ChangeState(0);
	state = LOOKING;

	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mPerceptionModule->SetMomorySpan(3.0f);
	mVisualSensor = mPerceptionModule->AddSensore<VisualSensor>();
	mVisualSensor->targetType = Types::PeonID;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mPursuitBehavior = mSteeringModule->AddBehavior<AI::PursuitBehavior>();
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
	mWanderBehavior->SetActive(true);

	for (int i = 0; i < mTextureIDs.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "carrier_%02i.png", i + 1);
		mTextureIDs[i] = X::LoadTexture(name);
	}

	float spriteWidth = X::GetSpriteWidth(mTextureIDs[0]);
	radius = spriteWidth;
}

void Wolf::Unload()
{
	Terminate();
}

void Wolf::Update(float dt)
{
	mVisualSensor->viewRange = viewRange;
	mVisualSensor->viewHalfAngle = viewAngle * X::Math::kDegToRad;

	mPerceptionModule->Update(dt);

	mStateMachine->Update(dt);
	
	const auto& memoryRecords = mPerceptionModule->GetMemoryRecords();
	for (auto& memory : memoryRecords)
	{
		auto pos = memory.GetProperty<X::Math::Vector2>("lastSeenPosition");
		X::DrawScreenLine(position, pos, X::Colors::Red);

		for (auto& entity : world.GetEntities())
		{
			if (X::Math::Magnitude(pos - entity->position) < 5 && X::Math::Magnitude(pos - entity->position) > 5 && target == nullptr)
			{
				//target = entity;
				ChangeState(CHASING);
				SetWander(false);
				mWanderBehavior->SetActive(false);
				mPursuitBehavior->SetActive(true);
			}
		}

		std::string score = std::to_string(memory.importance);
		X::DrawScreenText(score.c_str(), pos.x, pos.y, 12.0f, X::Colors::White);
	}
}

void Wolf::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTextureIDs.size()) % mTextureIDs.size();
	X::DrawSprite(mTextureIDs[frame], position);
}

void Wolf::ShowDebug(bool debug)
{
	mPursuitBehavior->ShowDebug(debug);
	mWanderBehavior->ShowDebug(debug);
}

void Wolf::ChangeState(WolfStates newState)
{
	mStateMachine->ChangeState((int)newState);
	state = newState;
}

void Wolf::Terminate()
{
	delete mStateMachine;
	mStateMachine = nullptr;
}
