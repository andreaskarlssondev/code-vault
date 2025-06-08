#pragma once

#include <vector>

class FSMTransition;
class FSMState
{
	public:
	
		virtual void Enter() { __noop;  }
		virtual void Update(const float aDeltaTime) = 0;
		virtual void Exit() { __noop; }

		inline void AddTransition(FSMTransition& aTransition) { myTransitions.emplace_back(&aTransition); }
		inline const std::vector<FSMTransition*>& GetTransitions() const { return myTransitions; }
		
	private:
		std::vector<FSMTransition*> myTransitions;
};