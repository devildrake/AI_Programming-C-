#include "GraphBehavior.h"

std::vector<ConnectionBehavior>GraphBehavior::GetConnections(NodeBehavior* fromNode) {
	std::vector<ConnectionBehavior> temp;
	for (int i = 0; i < connections.size(); i++) {
		if (EqualNode(*fromNode, *connections[i].GetFromNode())) {
			temp.push_back(connections[i]);
		}
	}
	return temp;
}