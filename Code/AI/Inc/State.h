#pragma once

namespace AI
{
	template <class Agent>
	class State
	{
	public:
		virtual ~State() = default;
		virtual void Enter(Agent& agent) = 0;
		virtual void Update(Agent& agent, float dt) = 0;
		virtual void Exit(Agent& agent) = 0;
	};
}
