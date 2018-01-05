#pragma once
#include "State.h"
class StateBank : public State {

public:

	virtual void Enter();
	virtual void Exit();
	virtual void Update(float);
	virtual std::string GetName();
	StateBank(Agent*, Vector2D);
};