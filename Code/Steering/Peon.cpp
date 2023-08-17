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
	const int frame = 0;
	X::Math::Vector2 pos;
	pos.x = X::GetScreenWidth() * 0.5f;
	pos.y = X::GetScreenHeight() * 0.5f;
	X::DrawSprite(mTextureIDs[frame], pos);
}

void Peon::ShowDebug(bool debug)
{
}
