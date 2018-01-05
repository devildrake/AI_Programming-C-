#pragma once
#include "Agent.h"
#include <string>
class Agent;

class State{
private:

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float) = 0;
	virtual std::string GetName() = 0;
	Vector2D entrance;
protected:
	Agent* agent;

};
