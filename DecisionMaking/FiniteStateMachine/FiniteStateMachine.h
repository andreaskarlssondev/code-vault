#pragma once

#include <vector>

class FSMState;

class FiniteStateMachine
{
	public:
		FiniteStateMachine() = default;
		virtual ~FiniteStateMachine();

		void Init(FSMState& aInitialState);

		void Update(const float aDeltaTime);

		inline void AddState(FSMState& aState) { myStates.emplace_back(&aState); }

	private:
		std::vector<FSMState*> myStates;
		FSMState* myInitialState;
		FSMState* myCurrentState;
};