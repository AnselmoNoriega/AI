#include "Peon.h"
#include "TypeIDs.h"

Peon::Peon(AI::AIWorld& world)
	: Agent(world, Types::PeonID)
{
}

void Peon::Load()
{
	for (int i = 0; i < mTextureIDs.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "scv_%02i.png", i + 1);
		mTextureIDs[i] = X::LoadTexture(name);
	}
}

void Peon::Unload()
{

}

void Peon::Update(float dt)
{

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
}
