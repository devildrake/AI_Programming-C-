#pragma once
#include "State.h"
class StateBank : public State {

public:

	virtual void Enter();
	virtual void Exit();
	virtual void Update(float);
	StateBank(Agent*, Vector2D);
};