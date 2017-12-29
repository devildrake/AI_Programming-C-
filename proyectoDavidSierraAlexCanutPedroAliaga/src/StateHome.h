#pragma once
#include "State.h"

class StateHome : public State {
	
public:

	virtual void Enter();
	virtual void Exit();
	virtual void Update(float);
	StateHome(Agent*, Vector2D);

};