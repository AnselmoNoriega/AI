#include "Precompiled.h"
#include "AIWorld.h"

using namespace AI;

void AIWorld::Initialize()
{

}

void AIWorld::Update()
{

}

void AIWorld::Register(Entity* entity)
{
	XASSERT(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end(), "AIWorld: entity already added!");
	mEntities.push_back(entity);
}

void AIWorld::Unregister(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);

	if (iter != mEntities.end())
	{
		mEntities.erase(iter);
	}
}

EntityPtrs AIWorld::GetEntitiesInRange(const X::Math::Circle& range, uint32_t typeID)
{
	float radiusSq = range.radius * range.radius;
	EntityPtrs entities;

	for (auto& entity : mEntities)
	{
		if (typeID == 0 || entity->GetTypeID() == typeID)
		{
			auto distVect = entity->position - range.center;

			if (X::Math::MagnitudeSqr(distVect) <= radiusSq)
			{
				entities.push_back(entity);
			}
		}
	}

	return entities;
}
