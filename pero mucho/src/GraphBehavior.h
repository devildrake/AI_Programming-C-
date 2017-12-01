#pragma once
#include "ConnectionBehavior.h"
#include <vector>
class GraphBehavior
{
public:
	// Returns an array of connections outgoing from the given node
	std::vector<ConnectionBehavior> GetConnections(NodeBehavior* fromNode);

	bool EqualNode(NodeBehavior a, NodeBehavior b) {
		return (a.tag == b.tag);
	}
	std::vector<ConnectionBehavior> connections;

};