#pragma 
#include "Node.h"
#include "Connection.h"
#include "Graph.h"

class State
{
private:
	

public:
	State();
	~State();

	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};