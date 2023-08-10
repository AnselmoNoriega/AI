#include "Precompiled.h"
#include "Entity.h"
#include "AIWorld.h"

using namespace AI;

Entity::Entity(AIWorld& world, uint32_t typeID)
	: world(world),
	mUniqueID(static_cast<uint64_t>(typeID) << 32 | world.GetNextID())
{
	world.Register(this);
}

Entity::~Entity()
{
	world.Unregister(this);
}
