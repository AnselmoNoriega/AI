#include "VisualSensor.h"

void VisualSensor::Update(AI::Agent& agent, AI::MemoryRecords& memory, float dt)
{
	const auto& viewRangeSqr = viewRange * viewRange;
	const auto& entities = agent.world.GetEntities();

	for (auto& entity : entities)
	{
		if (entity == &agent)
		{
			continue;
		}

		X::Math::Vector2 posToTarget = entity->position - agent.position;
		if (X::Math::MagnitudeSqr(posToTarget) > viewRangeSqr)
		{
			continue;
		}

		X::Math::Vector2 dirToTarget = X::Math::Normalize(posToTarget);
		float dot = X::Math::Dot(agent.heading, dirToTarget);
		float angleToTarget = acos(dot);

		if (angleToTarget > viewHalfAngle)
		{
			continue;
		}

		auto iter = memory.begin();
		for (; iter != memory.end(); ++iter)
		{
			if (iter->uniqueID == entity->GetUniqueID())
			{
				break;
			}
		}

		if (iter != memory.end())
		{
			iter->properties["lastSeenPosition"] = entity->position;
			iter->lastRecordedTime = X::GetTime();
		}
		else
		{
			auto& newRecord = memory.emplace_back();
			newRecord.uniqueID = entity->GetUniqueID();
			newRecord.properties["lastSeenPosition"] = entity->position;
			newRecord.lastRecordedTime = X::GetTime();
		}

		auto fovStart = X::Math::Rotate(agent.heading * viewRange, -viewHalfAngle);
		auto fovEnd = X::Math::Rotate(agent.heading * viewRange, viewHalfAngle);
		X::DrawScreenLine(agent.position, agent.position + fovStart, X::Colors::Cyan);
		X::DrawScreenLine(agent.position, agent.position + fovEnd, X::Colors::Cyan);

		auto angle = atan2(agent.heading.y, agent.heading.x);
		X::DrawScreenArc(agent.position, viewRange, angle - viewHalfAngle, angle + viewHalfAngle, X::Colors::LightCyan);
	}
}
