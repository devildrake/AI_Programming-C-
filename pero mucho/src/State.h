#pragma 
#include "Node.h"
#include "Connection.h"
#include "Graph.h"

class State
{
private:
	

public:
	explicit State() = default;
	virtual ~State() = default;

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};