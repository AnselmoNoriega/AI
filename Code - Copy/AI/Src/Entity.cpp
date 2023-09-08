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

X::Math::Matrix3 Entity::GetWorldTransform() const
{
	const auto h = heading;
	const auto s = X::Math::PerpendicularRH(h);
	const auto d = position;

	return
	{
		s.x, s.y, 0.0,
		h.x, h.y, 0.0,
		d.x, d.y, 1.0f
	};
}
