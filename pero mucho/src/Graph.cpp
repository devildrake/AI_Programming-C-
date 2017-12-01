#include "Graph.h"

std::vector<Connection>Graph::GetConnections(Node* fromNode) {
	std::vector<Connection> temp;
	for (int i = 0; i < connections.size(); i++) {
		if (EqualNode(*fromNode, *connections[i].GetFromNode())) {
			temp.push_back(connections[i]);
		}
	}
	return temp;
}