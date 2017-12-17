#pragma once
#include "Connection.h"
#include <vector>
class Graph
{
public:
	// Returns an array of connections outgoing from the given node
	std::vector<Connection> GetConnections(Node* fromNode);

	bool EqualNode(Node a, Node b) {
		return (a.GetCoords() == b.GetCoords());
	}

	static bool EqualVector(Vector2D a, Vector2D b) {
		bool temp = true;
		if (a.x != b.x || a.y != b.y) {
			temp = false;
		}
		return temp;
	}


	std::vector<Connection> connections;

};