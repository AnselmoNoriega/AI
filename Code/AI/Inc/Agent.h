#pragma once
#include "Entity.h"

namespace AI
{
	class Agent;
	using AgentPtrs = std::vector<Agent*>;

	class Agent: public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeID);
		~Agent() override = default;
	};
}