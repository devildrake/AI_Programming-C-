#pragma once
#include "State.h"

class StateSaloon : public State {
	
public:
	virtual void Enter();
	virtual void Exit();
	virtual void Update();

};