#include "ConnectionBehavior.h"

NodeBehavior* ConnectionBehavior::GetFromNode() {
	return &from;
}

NodeBehavior* ConnectionBehavior::GetToNode() {

	return &to;
}

float ConnectionBehavior::GetCost() {
	return cost;
}

ConnectionBehavior::ConnectionBehavior(NodeBehavior a, NodeBehavior b) {
	from = a;
	to = b;
}

