#pragma once
#include "Agent.h"
class Agent;

class State{
private:

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float) = 0;
	Vector2D entrance;
protected:
	Agent* agent;

};
