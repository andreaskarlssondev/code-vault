#include "FiniteStateMachine.h"

#include "FSMState.h"
#include "FSMTransition.h"

#include <assert.h>

FiniteStateMachine::~FiniteStateMachine()
{
	if (myCurrentState)
	{
		myCurrentState->Exit();
	}

	for (auto* state : myStates)
	{
		delete state;
	}
}

void FiniteStateMachine::Init(FSMState& aInitialState)
{
	myInitialState = &aInitialState;
	myCurrentState = myInitialState;
	myCurrentState->Enter();
}

void FiniteStateMachine::Update(const float aDeltaTime)
{
	for (auto& transition : myCurrentState->GetTransitions())
	{
		if (transition->IsValid())
		{
			myCurrentState->Exit();
	
			myCurrentState = transition->GetState();
		
			transition->OnTransition();
			myCurrentState->Enter();
			
			/*
				Return here instead of break if we are going to transition again from current state, 
				do not start using the state before we know that it is the state we want
			*/
			return;
		}
	}

	myCurrentState->Update(aDeltaTime);
}

