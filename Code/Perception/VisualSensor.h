#pragma once

#include <AI.h>

class VisualSensor : public AI::Sensor
{
public:
	void Update(AI::Agent& agent, AI::MemoryRecords& memory, float dt) override;

	float viewRange = 0.0f;
	float viewHalfAngle = 0.0f;
};