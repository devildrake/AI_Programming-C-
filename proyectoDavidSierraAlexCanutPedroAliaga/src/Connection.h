#pragma once
#include "Node.h"
#include "Scene.h"
class Connection
{
private:
	float cost;
	Node from;
	Node to;
public:

	Connection(Node, Node);
	// Returns the non-negative cost of the connection
	float GetCost();
	// Returns the node that this connection came from
	Node* GetFromNode();
	// Returns the node that this connection leads to
	Node* GetToNode();
};