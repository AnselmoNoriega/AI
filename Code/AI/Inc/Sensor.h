#pragma once


#include "MemoryRecord.h"

namespace AI
{
	class Agent;

	class Sensor
	{
	public:
		virtual ~Sensor() = default;

		virtual void Update(Agent& agent, MemoryRecords& memory, float dt) = 0;
	};
}