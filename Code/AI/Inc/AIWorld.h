#pragma once

#include "Entity.h"

namespace AI
{
	class AIWorld
	{
	public:
		void Initialize();
		void Update();

		void Register(Entity* entity);
		void Unregister(Entity* entity);

		EntityPtrs GetEntities() const { return mEntities; }

		EntityPtrs GetEntitiesInRange(const X::Math::Circle& range, uint32_t typeID);

		uint32_t GetNextID() const
		{
			XASSERT(mNextID < UINT32_MAX, "AIWorld: run out of Ids!");
			return mNextID++;
		}

	private:
		mutable uint32_t mNextID = 0;
		EntityPtrs mEntities;
	};
}