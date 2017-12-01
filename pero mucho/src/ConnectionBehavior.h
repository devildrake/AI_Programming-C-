#pragma once
#include "NodeBehavior.h"
#include "Scene.h"
class ConnectionBehavior
{
private:
	float cost;
	NodeBehavior from;
	NodeBehavior to;
public:

	ConnectionBehavior(NodeBehavior, NodeBehavior);
	// Returns the non-negative cost of the connection
	float GetCost();
	// Returns the node that this connection came from
	NodeBehavior* GetFromNode();
	// Returns the node that this connection leads to
	NodeBehavior* GetToNode();
};