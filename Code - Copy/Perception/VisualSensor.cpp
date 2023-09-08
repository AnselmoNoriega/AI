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

		if (targetType != Types::Invalid && targetType != entity->GetTypeID())
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

		X::Math::LineSegment lineToTarget(agent.position, entity->position);
		if (!agent.world.HasLineOfSight(lineToTarget))
		{
			X::DrawScreenLine(agent.position, entity->position, X::Colors::Yellow);
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
			newRecord.properties["type"] = static_cast<int>(entity->GetTypeID());
			newRecord.lastRecordedTime = X::GetTime();
		}
	}

	auto fovStart = X::Math::Rotate(agent.heading * viewRange, -viewHalfAngle);
	auto fovEnd = X::Math::Rotate(agent.heading * viewRange, viewHalfAngle);
	X::DrawScreenLine(agent.position, agent.position + fovStart, X::Colors::Cyan);
	X::DrawScreenLine(agent.position, agent.position + fovEnd, X::Colors::Cyan);

	auto angle = atan2(agent.heading.y, agent.heading.x);
	X::DrawScreenArc(agent.position, viewRange, angle - viewHalfAngle, angle + viewHalfAngle, X::Colors::LightCyan);
}
