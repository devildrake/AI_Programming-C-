#pragma once
#include "State.h"


class StateMine : public State {

public:

	virtual void Enter();
	virtual void Exit();
	virtual void Update();
};
