#pragma once

class FSMState;
class FSMTransition
{
	public:
		virtual bool IsValid() = 0;
		virtual FSMState* GetState() = 0;
		virtual void OnTransition() { __noop; }
};