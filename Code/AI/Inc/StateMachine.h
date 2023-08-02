#pragma once
#include "State.h"

namespace AI
{
	template <class Agent>
	class StateMachine final
	{
	public:
		StateMachine(Agent& agent):
			mAgent(agent)
		{
			
		}

		template<class NewState>
		void AddState()
		{
			static_assert(std::is_base_of_v<State<Agent>, NewState>, "StateMachine: can only add stateTypes");
			mStates.push_back(std::make_unique<NewState>());
		}

		void Update(float dt)
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->Update(mAgent, dt);
			}
		}

		void ChangeState(int index)
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->Exit(mAgent);
			}

			mCurrentState = mStates[index].get();
			mCurrentState->Enter(mAgent);
		}
	private:
		Agent& mAgent;
		State<Agent>* mCurrentState = nullptr;
		std::vector<std::unique_ptr<State<Agent>>> mStates;
	};
}