#pragma once
#include "Node.h"
#include "Connection.h"
#include "Graph.h"

class State{
private:
	

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
};
