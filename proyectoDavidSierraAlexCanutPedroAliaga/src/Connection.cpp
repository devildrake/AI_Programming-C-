#include "Connection.h"

Node* Connection::GetFromNode() {
	return &from;
}

Node* Connection::GetToNode() {

	return &to;
}

float Connection::GetCost() {
	return cost;
}

Connection::Connection(Node a, Node b) {
	from = a;
	to = b;
	cost = a.GetCost();
}

